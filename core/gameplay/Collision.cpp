#include "Collision.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"
#include <iostream>
#include <memory>

using namespace Collision;

BoundingBox::BoundingBox(glm::vec3 position) : position{position} {}

Collisioner::Collisioner() {
  entity = std::nullopt;
  boundingbox = new AABoundingBox(glm::vec3{0.f}, glm::vec3{0.f},
                                  glm::vec3{0.f}); // single point
}

Collisioner::Collisioner(Entity *entity, BoundingBox *boundingbox)
    : entity(entity), boundingbox(boundingbox) {}

Collisioner::Collisioner(Entity *entity, BoundingBox *boundingbox,
                         std::string tag)
    : entity(entity), boundingbox(boundingbox), tag{tag} {}

void Collisionable::collide(Collisionable &other) {
  if (!active || !other.isActive())
    return;

  for (const auto &own_col : collisioners) {
    for (const auto &other_col : other.getCollisioners()) {
      if (collide(own_col, other_col)) {
        onCollide(other_col);
      }
    }
  }
}

bool Collisionable::collide(const Collisioner &own,
                            const Collisioner &other) const {
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

bool AABBCollisionerOctreeNode::insert(Collisioner const *collisioner) {
  const auto bb = collisioner->getBoundingBox();

  // Check if objects fits in boundingbox
  if (!bb->collideWith(boundingbox))
    return false;
  ;

  // Check if bb is smaller then the current bounding box
  auto fits = bb->getSize().x < boundingbox.getSize().x &&
              bb->getSize().y < boundingbox.getSize().y &&
              bb->getSize().z < boundingbox.getSize().z;

  if (fits) {
    int index = getIndex(bb->getCenter());

    // create new node
    if (!children[index]) {
      AABoundingBox new_bb = calculateBoundingBoxForChild(index);
      children[index] = std::make_unique<AABBCollisionerOctreeNode>(new_bb);
    }
    return children[index]->insert(collisioner);

  } else {
    collisioners.push_back(collisioner);
    return true;
  }
}

int AABBCollisionerOctreeNode::getIndex(const glm::vec3 position) const {
  int index = 0;
  if (position.x >= boundingbox.getCenter().x)
    index |= 4;
  if (position.y >= boundingbox.getCenter().y)
    index |= 2;
  if (position.z >= boundingbox.getCenter().z)
    index |= 1;
  return index;
}

AABoundingBox AABBCollisionerOctreeNode::calculateBoundingBoxForChild(int index) {
  const auto size = boundingbox.getSize();
  const glm::vec3 pos = glm::vec3{
    index & 4 ? boundingbox.getPosition().x +  (size.x / 2) : boundingbox.getPosition().x,
    index & 2 ? boundingbox.getPosition().y +  (size.y / 2) : boundingbox.getPosition().y,
    index & 1 ? boundingbox.getPosition().z +  (size.z / 2) : boundingbox.getPosition().z,
  };

  return AABoundingBox(pos, pos, pos + size / 2.f);
}

void AABBCollisionerOctreeNode::query(const Collisioner& other, std::vector<const Collisioner*> &found) {
  if(!other.getBoundingBox()->collideWith(boundingbox)) return;

  for(const auto& collisioner: collisioners){
    if(other.getBoundingBox()->collides(*collisioner->getBoundingBox())) {
      found.push_back(collisioner);
    }
  }

  for(const auto& child : children) {
    if(child){
      child->query(other, found);
    }
  }
}

CollisionerOctree::CollisionerOctree(){
  auto bb = AABoundingBox({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {4.f, 4.f, 4.f});
  root = std::make_unique<AABBCollisionerOctreeNode>(bb);
}
