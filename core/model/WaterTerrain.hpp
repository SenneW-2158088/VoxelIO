#pragma once

#include "gameplay/Terrain.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "manager/AssetManager.h"

class WaterTerrain : public Terrain {

private:
  float prev_time{0.f};
  std::vector<Mesh::Vertex> vertices = {
    // Vertex data for the quad
    {{-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
};
  std::vector<unsigned int> indices = {
      0, 1, 2,
      1, 3, 2
  };
  Shader *shader;
  Mesh::InstancedMesh *plane;


public:
  WaterTerrain(){
    shader = AssetManager::getShader("water");
    std::vector<glm::vec3> positions{};
    const auto offset = floor((2 + 3 * 32) / 2);

    for (int x = base_position.x - offset; x < base_position.x + offset; x++) {
      for (int z = base_position.z - offset; z < base_position.z + offset; z++) {
        positions.push_back(glm::vec3{x, 0.f, z});
      }
    }

    plane = new Mesh::InstancedMesh(vertices, indices, nullptr, {positions}, {base_position});
    plane->scale(glm::vec3(100.f));
    // plane->scaleToWorld(glm::vec3(16, 0.f, 16.f));
  };
  void draw() const override { 
    plane->draw(shader); 
  };
  void update(const float dt) override{
    prev_time += dt * 0.1;
    shader->use();
    shader->setFloat("time", prev_time);
  };
  void collide(Collision::Collisionable &other) override{};
};
