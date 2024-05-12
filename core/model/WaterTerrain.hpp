#pragma once

#include "gameplay/Terrain.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "manager/AssetManager.h"

class WaterTerrain : public Terrain {
private:
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
  Mesh::Mesh *plane;


public:
  WaterTerrain(){
    shader = AssetManager::getShader("water");
    plane = new Mesh::Mesh(vertices, indices, nullptr);
    plane->scale(glm::vec3(10000.f));
  };
  void draw() const override { plane->draw(shader); };
  void update(const float dt) override{
    shader->setFloat("time", dt);
  };
  void collide(Collision::Collisionable &other) override{};
};
