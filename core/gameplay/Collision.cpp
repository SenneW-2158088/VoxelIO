#include "Collision.h"
#include "glm/common.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"
#include <iostream>
#include <memory>

using namespace Collision;

BoundingBox::BoundingBox(glm::vec3 position) : position{position} {}
BoundingBox::BoundingBox(glm::vec3 position, glm::vec3 size) : position{position}, size{size} {}

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
      if (collide(*own_col, *other_col)) {
        onCollide(*own_col, *other_col);
        other.onCollide(*other_col, *own_col);
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

AABoundingBox::AABoundingBox(glm::vec3 position, glm::vec3 size)
    : BoundingBox{position, size}, min{0.f}, max{size}{}

AABoundingBox::AABoundingBox(glm::vec3 position, Mesh::BaseMesh *mesh)
    : BoundingBox{position}, min{}, max{} {
  for (const auto &vertex : mesh->getVertices()) {
    min = glm::min(min, vertex.position);
    max = glm::max(max, vertex.position);
  }
}

bool AABoundingBox::collides(const BoundingBox &other) const {
  if(!this->active || !other.isActive()){
    return false;
  }

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

bool AABoundingBox::collideWith(const Ray &other) const {
  // std::cout << "in here not good" << std::endl;
  return false;
}

glm::vec3 AABoundingBox::calculatePenetration(const BoundingBox &other) const {
  return other.calculatePenetrationFor(*this);
}

glm::vec3 AABoundingBox::calculatePenetrationFor(const AABoundingBox &other) const {
  return glm::min(other.getMax() - getMin(), getMax() - other.getMin());
}

bool AABBCollisionerOctreeNode::insert(Collisioner const *collisioner) {
  const auto bb = collisioner->getBoundingBox();

  // std::cout << "Checking for: " << glm::to_string(bb->getPosition()) << " - " << glm::to_string(bb->getSize()) << std::endl;

  // Check if objects fits in boundingbox
  if (!bb->collideWith(boundingbox)) return false;

  // Check if bb is smaller then the current bounding box
  auto fits = bb->getSize().x < boundingbox.getSize().x / 2.f &&
              bb->getSize().y < boundingbox.getSize().y / 2.f &&
              bb->getSize().z < boundingbox.getSize().z / 2.f;

  if (fits) {
    // std::cout << "fits" << std::endl;
    int index = getIndex(bb->getCenter());

    // create new node
    if (!children[index]) {
      AABoundingBox new_bb = calculateBoundingBoxForChild(index);

      // std::cout << "creating new child" << std::endl;
      // std::cout << "Created new bounding box: " << glm::to_string(new_bb.getPosition()) << " - " << glm::to_string(new_bb.getSize());
      children[index] = std::make_unique<AABBCollisionerOctreeNode>(new_bb);
    }
    // std::cout << "Adding to child" << std::endl;
    return children[index]->insert(collisioner);

  } else {
    // std::cout << "doesnt fit" << std::endl;
    // std::cout << "Adding to this box" << std::endl;
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

  return AABoundingBox(pos, {0.f, 0.f, 0.f}, size / 2.f);
}

void AABBCollisionerOctreeNode::query(const Collisioner& other, std::vector<const Collisioner*> &found) {
  if(!other.getBoundingBox()->collideWith(boundingbox)) return;

  for(const auto& collisioner: collisioners){
    if(collisioner->getBoundingBox()->collides(*other.getBoundingBox())) {
      found.push_back(collisioner);
    }
  }

  for(const auto& child : children) {
    if(child){
      child->query(other, found);
    }
  }
}

CollisionerOctree::CollisionerOctree(glm::vec3 position, glm::vec3 size){
  auto bb = AABoundingBox(position, size);
  root = std::make_unique<AABBCollisionerOctreeNode>(bb);
}

CollisionerOctree::CollisionerOctree(AABoundingBox boundingbox){
  root = std::make_unique<AABBCollisionerOctreeNode>(boundingbox);
}

void CollisionerOctree::print_tree() {
  std::cout << "printing octree" << std::endl;
  root->print_node(0);  
}

void AABBCollisionerOctreeNode::print_node(int index) {
  std::cout << std::string(index, '-');
  std::cout << "Node: " << glm::to_string(boundingbox.getPosition()) << " - " << glm::to_string(boundingbox.getSize()) << std::endl;

  std::cout << std::string(index, '-');
  std::cout << "Collisioners: " << collisioners.size() << std::endl;;
  for (const auto & col : collisioners){
    std::cout << "- " << col->getTag() << std::endl;
  }

  std::cout << std::string(index, '-');
  std::cout << "Children: " << std::endl;
  for( const auto & child : children) {
    if (child) {
      child->print_node(index+1);
      std::cout << std::endl;
    }
  }

}

// Ray collision

Ray::Ray(glm::vec3 position) : BoundingBox(position, glm::normalize(glm::vec3{1.f, 0.f, 0.f})), direction{1.f, 0.f, 0.f} {}
Ray::Ray(glm::vec3 position, glm::vec3 direction) : BoundingBox(position, glm::normalize(direction)), direction{direction} {}

bool Ray::collides(const BoundingBox& other) const {
  // std::cout << "ray on: " << glm::to_string(this->position) << " dir: " << glm::to_string(direction) << std::endl;
  return other.collideWith(*this);
}

bool Ray::collideWith(const AABoundingBox &other) const {
    float tmin = (other.getMin().x - position.x) / direction.x; 
    float tmax = (other.getMax().x - position.x) / direction.x; 

    if (tmin > tmax) std::swap(tmin, tmax); 

    float tymin = (other.getMin().y - position.y) / direction.y; 
    float tymax = (other.getMax().y - position.y) / direction.y; 

    if (tymin > tymax) std::swap(tymin, tymax); 

    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 

    if (tymin > tmin) tmin = tymin; 
    if (tymax < tmax) tmax = tymax; 

    float tzmin = (other.getMin().z - position.z) / direction.z; 
    float tzmax = (other.getMax().z - position.z) / direction.z; 

    if (tzmin > tzmax) std::swap(tzmin, tzmax); 

    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 

    if (tzmin > tmin) tmin = tzmin; 
    if (tzmax < tmax) tmax = tzmax; 

    return true;
}

bool Ray::collideWith(const Ray &other) const {
  
}

glm::vec3 Ray::calculatePenetration(const BoundingBox &other) const {
  
}

glm::vec3 Ray::calculatePenetrationFor(const AABoundingBox &other) const {
  
}

glm::vec3 Ray::calculatePenetrationFor(const Ray &other) const {
  
}


