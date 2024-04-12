#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <memory>
#include <optional>

namespace Collision {
class AABoundingBox;

class BoundingBox {
private:
protected:
  glm::vec3 position; // Could get the position from the entity but this is more
  glm::vec3 size; // size of the bounding box in each direction

public:
  BoundingBox(glm::vec3 position);
  BoundingBox(glm::vec3 position, glm::vec3 size);
  virtual bool collides(const BoundingBox &other) const { return false; };
  virtual bool collideWith(const AABoundingBox &other) const { return false; };

public:
  inline void setPosition(glm::vec3 position) { this->position = position; };
  inline glm::vec3 getPosition() const { return position; }

  virtual inline glm::vec3 getCenter() const { return position; };
  virtual inline glm::vec3 getSize() const { return size; };
};

class AABoundingBox : public BoundingBox {
protected:
  glm::vec3 min, max;

public:
  AABoundingBox(glm::vec3 position, Mesh::BaseMesh *mesh);
  AABoundingBox(glm::vec3 position, glm::vec3 min, glm::vec3 max);
  AABoundingBox(glm::vec3 position, glm::vec3 size);
  bool collides(const BoundingBox &other) const override;
  bool collideWith(const AABoundingBox &other) const override;

public:
  glm::vec3 getMin() const { return min + position; };
  glm::vec3 getMax() const { return max + position; };
  inline glm::vec3 getCenter() const override { return (getMin() + getMax()) * .5f; };
  inline glm::vec3 getSize() const override { return (getMax() - getMin()); }
};

class Collisioner {
private:
  std::string tag = "[BoundingBox]";
  std::optional<Entity *> entity;
  BoundingBox *boundingbox;

public:
  std::optional<Entity *> getEntity() const { return entity; };
  inline std::string getTag() const { return tag; };
  BoundingBox *getBoundingBox() const { return boundingbox; };

public:
  Collisioner();
  Collisioner(Entity *entity, BoundingBox *boundingbox);
  Collisioner(Entity *entity, BoundingBox *boundingbox, std::string tag);
};

class Collisionable {
protected:
  std::vector<Collisioner* > collisioners;
  bool active = true; // if set to false, disables collision
  bool collide(const Collisioner &own, const Collisioner &other) const;

public:
  inline std::vector<Collisioner* > &getCollisioners() { return collisioners; };
  inline void setCollisioners(std::vector<Collisioner*> collisioners) {
    this->collisioners = collisioners;
  };
  inline bool isActive() const { return active; };
  inline void setActive(bool activation) { this->active = activation; };
  inline void addCollsioner(Collisioner* collisioner) {
    collisioners.push_back(collisioner);
  };

public:
  virtual void collide(Collisionable &other);
  virtual void onCollide(const Collisioner &other){};
};

class AABBCollisionerOctreeNode {
private:
  std::vector<std::unique_ptr<AABBCollisionerOctreeNode>> children;
  std::vector<Collisioner const *> collisioners;
  AABoundingBox boundingbox;

private:
  int getIndex(const glm::vec3 position) const;
  AABoundingBox calculateBoundingBoxForChild(int index);

public:
  AABBCollisionerOctreeNode(AABoundingBox boundingbox)
      : boundingbox{boundingbox}, children(8) {}
  bool insert(Collisioner const *collisioner);
  void query(const Collisioner &other, std::vector<const Collisioner *> &found);
  void print_node(int index);
};

class CollisionerOctree {
private:
  std::unique_ptr<AABBCollisionerOctreeNode> root;

public:
  CollisionerOctree(glm::vec3 position, glm::vec3 size);
  CollisionerOctree(AABoundingBox boundingbox);

  inline void insert(Collisioner *collisioner) { root->insert(collisioner); }

  inline std::vector<const Collisioner *> query(const Collisioner &object) {
    std::vector<const Collisioner *> potential{};
    root->query(object, potential);
    return potential;
  }

  void print_tree();
};

}; // namespace Collision
