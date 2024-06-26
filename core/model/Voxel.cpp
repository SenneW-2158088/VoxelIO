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
  this->mesh = new Mesh::Mesh(vertices, indices, nullptr);
  this->shader->setBlockBinding("Matrices", 0);
  this->shader->setBlockBinding("DirectionalLightData", 1);
  this->mesh->move(this->position);
  this->mesh->scale(glm::vec3{1.f});

  // Setup collision

  Collision::Collisioner * collisioner = new Collision::Collisioner(
      this, new Collision::AABoundingBox(this->position - mesh->getTranslation(), mesh),
      "Voxel bounding box");

  addCollsioner(collisioner);
}

void Voxel::update(float dt) {}

void Voxel::draw() {
  shader->use();
  shader->setBool("highlighted", isHighlighted);
  texture->use();
  mesh->draw(shader);
  isHighlighted = false;
}

void Voxel::onCollide(const Collision::Collisioner& own, const Collision::Collisioner &other) {
  // std::cout << getName() << " collided with"
            // << other.getEntity().value()->getName() << std::endl;
}

InstancedVoxel::InstancedVoxel(std::vector<glm::vec3> positions, glm::vec3 position)
    : shader{AssetManager::getShader("instanced_voxel")},
      texture{AssetManager::getTexture("grass.jpg")},
      Collision::Collisionable{} {
  // TODO: remove hardcoded value
  this->position = position;
  // std::cout << "voxel mesh on: " << glm::to_string(position) << std::endl;
  this->mesh = new Mesh::InstancedMesh(vertices, indices, {}, positions, position);
  this->shader->setBlockBinding("Matrices", 0);
  this->shader->setBlockBinding("DirectionalLightData", 1);
  // this->shader->setResourceBinding("pls", 3);
  // this->mesh->move(this->position);
  // this->mesh->scale(glm::vec3{1.f});
  // std::cout << "created mesh" << glm::to_string(position) << std::endl;

  const auto bb =
      Collision::AABoundingBox(position, glm::vec3{0.f, 0.f, 0.f},glm::vec3{16.f, 16.f, 16.f});
  this->tree = new Collision::CollisionerOctree{bb};

  for (glm::vec3 &pos : positions) {
    Collision::Collisioner* collisioner = new Collision::Collisioner(
        this, new Collision::AABoundingBox(position + pos - mesh->getTranslation(), mesh), "Voxel Bounding Box");
    addCollsioner(collisioner);
    tree->insert(collisioner);
    this->positions.push_back(position + pos - mesh->getTranslation());
  }
}

void InstancedVoxel::draw() {
  if(highlighted.has_value()){
    shader->use();
    shader->setBool("highlighted", true);
    shader->setInt("highlighted_id", highlighted.value());
  }
  else{
    shader->use();
    shader->setBool("highlighted", false);
    
  }
  texture->use();
  mesh->draw(shader);

  highlighted = std::nullopt;
}

void InstancedVoxel::update(float dt) {}

void InstancedVoxel::collide(Collisionable &other) {
  if (!active || !other.isActive()){
    return;
  }

  for (auto &other_col : other.getCollisioners()){
    const auto found = tree->query(*other_col);
    for (const auto &own_col : found) {
      if(Collisionable::collide(*own_col, *other_col)) {
          // tempCollide(*own_col, *other_col);
         // onCollide(*other_col);
         onCollide(*own_col, *other_col);
         other.onCollide(*other_col, *own_col);
      }
    }
  }
}

void InstancedVoxel::onCollide(const Collision::Collisioner &own, const Collision::Collisioner &other) {

  // std::cout << "Block collided " << glm::to_string(own.getBoundingBox()->getPosition()) << std::endl;
}

void InstancedVoxel::destroy(glm::vec3 position) {
    auto index = getIndex(position);
    if (index != -1) {
      mesh->setActive(index, false);
      collisioners[index]->getBoundingBox()->setActive(false);
    } 
}

int InstancedVoxel::getHeight(glm::vec3 position){
  for (auto &pos : positions ){

    std::cout << "checking: " << glm::to_string(pos - glm::vec3(0.5f)) <<  std::endl;
    if((pos.x -.5f) == position.x && (pos.z -.5f)== position.z){
      std::cout << "found height block" << pos.y <<  std::endl;
      return pos.y + 1;
    }
  }

  std::cout << "found no matching height block" << std::endl;
  return 0;
}
