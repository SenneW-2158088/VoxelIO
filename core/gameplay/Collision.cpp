#include "Collision.h"
#include <iostream>

using namespace Collision;

Collisionable::Collisionable(Entity* entity, BoundingBox* boundingbox)
    : entity{entity}, boundingBox{boundingbox} {}

void Collisionable::collide(Collisionable &other) {
    BoundingBox* box = &other.getBoundingBox();
    if(this->getBoundingBox().collides(*box)){
        std::cout << "Colliding" << std::endl;
    }
}

bool AABoundingBox::collides(BoundingBox &other){
    return other.collideWith(*this);
}

bool AABoundingBox::collideWith(AABoundingBox &other){
    // handle collision
    return true;
    
}
