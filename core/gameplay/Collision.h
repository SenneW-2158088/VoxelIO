#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"
#include <glm/glm.hpp>
#include <optional>

namespace Collision {
class AABoundingBox;

class BoundingBox {
protected:
  glm::vec3 position; // Could get the position from the entity but this is more flexible
public:
  BoundingBox(glm::vec3 position);
  virtual bool collides(BoundingBox &other) { return false; };
  virtual bool collideWith(AABoundingBox &other) { return false; };
public:
  inline void setPosition(glm::vec3 position) { this->position = position;};
};

class AABoundingBox : public BoundingBox {
private:
  glm::vec3 min, max;

public:
  AABoundingBox(glm::vec3 position, glm::vec3 min, glm::vec3 max);
  AABoundingBox(glm::vec3 position, Mesh::Mesh *mesh);
  bool collides(BoundingBox &other) override;
  bool collideWith(AABoundingBox &other) override;
public:
  glm::vec3 getMin() const { return min + position; };
  glm::vec3 getMax() const { return max + position; };
};

class Collisioner {
private:
  std::optional<Entity *> entity;
  BoundingBox* boundingbox;

public:
  std::optional<Entity *> getEntity() const { return entity; };
  BoundingBox *getBoundingBox() { return boundingbox; };

public:
  Collisioner();
  Collisioner(Entity *entity, BoundingBox* boundingbox);
};

class Collisionable {
private:
  Collisioner collisioner;

public:
  inline void setCollisioner(Collisioner collisioner) {
    this->collisioner = collisioner;
  };

public:
  inline Collisioner &getCollisioner() { return collisioner; };

public:
  void collide(Collisionable &other);
  virtual void onCollide(Collisionable &other){};
};
}; // namespace Collision
