#include "Collision.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"
#include <iostream>

using namespace Collision;

BoundingBox::BoundingBox(glm::vec3 position) : position{position} {}

Collisioner::Collisioner() {
  entity = std::nullopt;
  boundingbox = new AABoundingBox(glm::vec3{0.f}, glm::vec3{0.f},
                                  glm::vec3{0.f}); // single point
}

Collisioner::Collisioner(Entity *entity, BoundingBox *boundingbox)
    : entity(entity), boundingbox(boundingbox) {}

Collisioner::Collisioner(Entity *entity, BoundingBox *boundingbox, std::string tag)
    : entity(entity), boundingbox(boundingbox), tag{tag} {}

void Collisionable::collide(Collisionable &other) {
  if(!active || !other.isActive()) return;

  for(const auto &own_col : collisioners){
    for(const auto &other_col : other.getCollisioners()){
      if(collide(own_col, other_col)){
        onCollide(other_col);
      }
    }
  }
}

bool Collisionable::collide(const Collisioner &own, const Collisioner &other) const {
  return own.getBoundingBox()->collides(*other.getBoundingBox());
}


AABoundingBox::AABoundingBox(glm::vec3 position, glm::vec3 min, glm::vec3 max)
    : BoundingBox{position}, min{min}, max{max} {}
    
AABoundingBox::AABoundingBox(glm::vec3 position, Mesh::BaseMesh *mesh)
    : BoundingBox{position} {
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

bool AABoundingBox::collides(const BoundingBox &other) const {
  return other.collideWith(*this);
}

bool AABoundingBox::collideWith(const AABoundingBox &other) const {
  return (this->getMin().x <= other.getMax().x &&
          this->getMax().x >= other.getMin().x &&
          this->getMin().y <= other.getMax().y &&
          this->getMax().y >= other.getMin().y &&
          this->getMin().z <= other.getMax().z &&
          this->getMax().z >= other.getMin().z);
}
