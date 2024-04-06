//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"
#include "gameplay/Collision.h"
#include "glm/fwd.hpp"

#include <manager/AssetManager.h>
#include <iostream>
#include <mutex>

Voxel::Voxel() :
        shader{AssetManager::getShader("voxel")},
        texture{AssetManager::getTexture("villager.jpg")},
        Collision::Collisionable{}
{
    this->mesh = new Mesh::Mesh(vertices, indices, {});
    this->position = glm::vec3{0.0f, 0.0f, 10.0f};
    this->shader->setBlockBinding("Matrices", 0);
    this->mesh->move(this->position);
    this->mesh->scale(glm::vec3{1.f});

    // Setup collision

    Collision::Collisioner collisioner = Collision::Collisioner(
      this,
      new Collision::AABoundingBox(this->position, mesh)
    );

    setCollisioner(collisioner);
}

void Voxel::update(float dt) {

}

void Voxel::draw() {
    texture->use();
    mesh->draw(shader);
}

void Voxel::onCollide(Collision::Collisionable &other) {
    std::cout << getName() << " collided with" << other.getCollisioner().getEntity().value()->getName() << std::endl;
}
