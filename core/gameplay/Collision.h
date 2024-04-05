#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"

namespace Collision {

// Only for now
class AABoundingBox;
  
class BoundingBox {
public:
  virtual bool collides(BoundingBox &other) = 0;
  virtual bool collideWith(AABoundingBox &other) = 0;
};

class AABoundingBox : BoundingBox {
public:
  AABoundingBox(Mesh::Mesh *mesh);
  bool collides(BoundingBox &other) override;
  bool collideWith(AABoundingBox &other) override;
};

class Collisionable {
protected:
  Entity* entity; // Entity reference for futute collision checks
  BoundingBox* boundingBox;

public:
  explicit Collisionable() = default;
  Collisionable(Entity* entity, BoundingBox* boundingbox);
  void collide(Collisionable &other);
  inline BoundingBox* getBoundingBox() { return boundingBox; };
  virtual void onCollide(Collisionable &other) = 0;
};
} // namespace Collision
