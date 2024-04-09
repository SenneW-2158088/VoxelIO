//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"
#include "gameplay/Collision.h"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"

#include <format>
#include <manager/AssetManager.h>
#include <iostream>

Voxel::Voxel(glm::vec3 position) :
        shader{AssetManager::getShader("voxel")},
        texture{AssetManager::getTexture("villager.jpg")},
        Collision::Collisionable{}
{
    this->position = position;
    this->mesh = new Mesh::Mesh(vertices, indices, {});
    this->shader->setBlockBinding("Matrices", 0);
    this->mesh->move(this->position);
    this->mesh->scale(glm::vec3{1.f});

    // Setup collision

    Collision::Collisioner collisioner = Collision::Collisioner(
      this,
      new Collision::AABoundingBox(this->position, mesh),
      "Voxel bounding box"
    );

    addCollsioner(collisioner);
}

void Voxel::update(float dt) {

}

void Voxel::draw() {
    texture->use();
    mesh->draw(shader);
}

void Voxel::onCollide(const Collision::Collisioner &other) {
    std::cout << getName() << " collided with" << other.getEntity().value()->getName() << std::endl;
}

InstancedVoxel::InstancedVoxel(std::vector<glm::vec3> positions) :
shader{AssetManager::getShader("instanced_voxel")},
texture{AssetManager::getTexture("villager.jpg")},
Collision::Collisionable{}
{
        // TODO: remove hardcoded value
    this->position = glm::vec3{16.f, 0.f, 0.f};
    this->mesh = new Mesh::InstancedMesh(vertices, indices, {}, positions);
    this->shader->setBlockBinding("Matrices", 0);
    this->mesh->move(this->position);
    this->mesh->scale(glm::vec3{1.f});

    for(glm::vec3 &pos : positions){
        Collision::Collisioner collisioner = Collision::Collisioner(this, new Collision::AABoundingBox(pos, mesh), "Voxel Bounding Box");

        addCollsioner(collisioner);
    }
}

void InstancedVoxel::draw() {
    texture->use();
    mesh->draw(shader);
}

void InstancedVoxel::update(float dt) {

}
