#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"
#include <glm/glm.hpp>
#include <optional>

namespace Collision {
class AABoundingBox;

class BoundingBox {
public:
  virtual bool collides(BoundingBox &other);
  virtual bool collideWith(AABoundingBox &other) { return false; };
};

class AABoundingBox : public BoundingBox {
private:
  glm::vec3 min, max;
public:
  AABoundingBox(glm::vec3 min, glm::vec3 max);
  AABoundingBox(Mesh::Mesh* mesh);
  bool collides(BoundingBox &other) override;
  bool collideWith(AABoundingBox &other) override;

public:
  glm::vec3 getMin() const { return min; };
  glm::vec3 getMax() const { return max; };
};

class Collisioner {
private:
  std::optional<Entity *> entity;
  BoundingBox boundingbox;

public:
  std::optional<Entity *> getEntity() const { return entity; };
  BoundingBox *getBoundingBox() {return &boundingbox;};

public:
  Collisioner();
};

class Collisionable {
private:
  Collisioner collisioner;

public:
  void collide(Collisionable &other);
  virtual void onCollide(Collisionable &other){};
};
}; // namespace Collision
