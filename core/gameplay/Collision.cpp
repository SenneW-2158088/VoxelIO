#include "Collision.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

using namespace Collision;

BoundingBox::BoundingBox(glm::vec3 position) : position{position}{}

Collisioner::Collisioner() {
  entity = std::nullopt;
  boundingbox = new AABoundingBox(glm::vec3{0.f}, glm::vec3{0.f}, glm::vec3{0.f}); //single point
}

Collisioner::Collisioner(Entity *entity, BoundingBox* boundingbox) 
: entity(entity), boundingbox(boundingbox){}

void Collisionable::collide(Collisionable &other) {
  BoundingBox *box = other.collisioner.getBoundingBox();
  if (this->collisioner.getBoundingBox()->collides(*box)) {
    std::cout << "Colliding" << std::endl;
  }
}

AABoundingBox::AABoundingBox(glm::vec3 position, glm::vec3 min, glm::vec3 max)
    : BoundingBox{position}, min{min}, max{max} {}

AABoundingBox::AABoundingBox(glm::vec3 position, Mesh::Mesh *mesh) : BoundingBox{position} {
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
  return (this->getMin().x <= other.getMax().x && this->getMax().x >= other.getMin().x && this->getMin().y <= other.getMax().y &&
          this->getMax().y >= other.getMin().y && this->getMin().z <= other.getMax().z && this->getMax().z >= other.getMin().z);
}
