//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"
#include "gameplay/Collision.h"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"

#include <format>
#include <iostream>
#include <manager/AssetManager.h>

Voxel::Voxel(glm::vec3 position)
    : shader{AssetManager::getShader("voxel")},
      texture{AssetManager::getTexture("villager.jpg")},
      Collision::Collisionable{} {
  this->position = position;
  this->mesh = new Mesh::Mesh(vertices, indices, {});
  this->shader->setBlockBinding("Matrices", 0);
  this->mesh->move(this->position);
  this->mesh->scale(glm::vec3{1.f});

  // Setup collision

  Collision::Collisioner * collisioner = new Collision::Collisioner(
      this, new Collision::AABoundingBox(this->position, mesh),
      "Voxel bounding box");

  addCollsioner(collisioner);
}

void Voxel::update(float dt) {}

void Voxel::draw() {
  texture->use();
  mesh->draw(shader);
}

void Voxel::onCollide(const Collision::Collisioner &other) {
  std::cout << getName() << " collided with"
            << other.getEntity().value()->getName() << std::endl;
}

InstancedVoxel::InstancedVoxel(std::vector<glm::vec3> positions)
    : shader{AssetManager::getShader("instanced_voxel")},
      texture{AssetManager::getTexture("villager.jpg")},
      Collision::Collisionable{} {
  // TODO: remove hardcoded value
  this->position = glm::vec3{0.f, 0.f, 0.f};
  this->mesh = new Mesh::InstancedMesh(vertices, indices, {}, positions);
  this->shader->setBlockBinding("Matrices", 0);
  this->mesh->move(this->position);
  this->mesh->scale(glm::vec3{1.f});

  const auto bb =
      Collision::AABoundingBox(position, glm::vec3{0.f, 0.f, 0.f},glm::vec3{16.f, 16.f, 16.f});
  this->tree = new Collision::CollisionerOctree{bb};

  for (glm::vec3 &pos : positions) {
    Collision::Collisioner* collisioner = new Collision::Collisioner(
        this, new Collision::AABoundingBox(pos, mesh), "Voxel Bounding Box");
    addCollsioner(collisioner);
    tree->insert(collisioner);
  }

  tree->print_tree();
}

void InstancedVoxel::draw() {
  texture->use();
  mesh->draw(shader);
}

void InstancedVoxel::update(float dt) {}

void InstancedVoxel::collide(Collisionable &other) {
  if (!active || !other.isActive()){
    return;
  }

  for (const auto &other_col : other.getCollisioners()){
    const auto found = tree->query(*other_col);
    for (const auto &own_col : found) {
      if(Collisionable::collide(*own_col, *other_col)) {
         onCollide(*other_col);
      }
    }
  }
}

void InstancedVoxel::onCollide(const Collision::Collisioner &other) {
  std::cout << "Player collided with block" << std::endl;
}
