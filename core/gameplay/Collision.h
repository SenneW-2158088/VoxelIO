#pragma once

#include "model/Entity.h"
#include <glm/glm.hpp>

namespace Collision {
class AABoundingBox;

class BoundingBox {
  virtual bool collides(BoundingBox &other);
  virtual void collideWith(AABoundingBox &other){};
};

class AABoundingBox : BoundingBox {
private:
  glm::vec3 min, max;

public:
  bool collides(BoundingBox &other) override;
  void collideWith(AABoundingBox &other) override;

public:
  glm::vec3 getMin() const { return min; };
  glm::vec3 getMax() const { return max;};
};

class Collisioner {
private:
  Entity *entity;
  BoundingBox boundingbox;
};

class Collisionable {
private:
  Collisioner collisioner;

public:
  void collide(Collisionable &other);
  virtual void onCollide(Collisionable &other){};
};
}; // namespace Collision
