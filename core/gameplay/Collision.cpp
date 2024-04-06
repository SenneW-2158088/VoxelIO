#include "Collision.h"
#include <iostream>

using namespace Collision;

Collisioner::Collisioner() {
  entity = std::nullopt;
  boundingbox = AABoundingBox(glm::vec3{0.f}, glm::vec3{0.f}); //single point
}

Collisioner::Collisioner(Entity *entity, BoundingBox boundingbox) 
: entity(entity), boundingbox(boundingbox){}

void Collisionable::collide(Collisionable &other) {
  BoundingBox *box = other.collisioner.getBoundingBox();
  if (this->collisioner.getBoundingBox()->collides(*box)) {
    std::cout << "Colliding" << std::endl;
  }
}

AABoundingBox::AABoundingBox(glm::vec3 min, glm::vec3 max)
    : min{min}, max{max} {}

AABoundingBox::AABoundingBox(Mesh::Mesh *mesh) {
  for (const auto &vertex : mesh->getVertices()) {
    if (vertex.position.x < min.x) {
      min.x = vertex.position.x;
    }
    if (vertex.position.y < min.y) {
      min.y = vertex.position.y;
    }
    if (vertex.position.z < min.z) {
      min.z = vertex.position.z;
    }

    if (vertex.position.x > max.x) {
      max.x = vertex.position.x;
    }
    if (vertex.position.y > max.y) {
      max.y = vertex.position.y;
    }
    if (vertex.position.z > max.z) {
      max.z = vertex.position.z;
    }
  }
}

bool AABoundingBox::collides(BoundingBox &other) {
  return other.collideWith(*this);
}

bool AABoundingBox::collideWith(AABoundingBox &other) {
  return (this->min.x <= other.getMax().x && this->max.x >= other.getMin().x && this->min.y <= other.getMax().y &&
          this->max.y >= other.getMin().y && this->min.z <= other.getMax().z && this->max.z >= other.getMin().z);
}
