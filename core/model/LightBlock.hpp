#pragma once

#include "glm/gtx/string_cast.hpp"
#include "graphics/Lighting.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "manager/AssetManager.h"
#include "model/Entity.h"
#include <iostream>
#include <vector>
class LightBlock : public Entity, public Lightable{
private:
  Shader *shader;
  Mesh::InstancedMesh* mesh;
  Material* material;

  const std::vector<Mesh::Vertex> vertices = {
      // Front face
      {{-0.5, -0.5, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
      {{0.5, -0.5, 0.5}, {0.0, 0.0, 1.0}, {1.0, 0.0}},
      {{0.5, 0.5, 0.5}, {0.0, 0.0, 1.0}, {1.0, 1.0}},
      {{-0.5, 0.5, 0.5}, {0.0, 0.0, 1.0}, {0.0, 1.0}},
      // Back face (reversed order)
      {{0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}, {0.0, 0.0}},
      {{-0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}, {1.0, 0.0}},
      {{-0.5, 0.5, -0.5}, {0.0, 0.0, -1.0}, {1.0, 1.0}},
      {{0.5, 0.5, -0.5}, {0.0, 0.0, -1.0}, {0.0, 1.0}},
      // Left face
      {{-0.5, -0.5, -0.5}, {-1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{-0.5, -0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{-0.5, 0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{-0.5, 0.5, -0.5}, {-1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Right face (reversed order)
      {{0.5, -0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{0.5, -0.5, -0.5}, {1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{0.5, 0.5, -0.5}, {1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{0.5, 0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Top face
      {{-0.5, 0.5, -0.5}, {0.0, 1.0, 0.0}, {0.0, 1.0}},
      {{-0.5, 0.5, 0.5}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
      {{0.5, 0.5, 0.5}, {0.0, 1.0, 0.0}, {1.0, 0.0}},
      {{0.5, 0.5, -0.5}, {0.0, 1.0, 0.0}, {1.0, 1.0}},
      // Bottom face
      {{-0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}, {1.0, 1.0}},
      {{-0.5, -0.5, 0.5}, {0.0, -1.0, 0.0}, {0.0, 1.0}},
      {{0.5, -0.5, 0.5}, {0.0, -1.0, 0.0}, {0.0, 0.0}},
      {{0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}, {1.0, 0.0}}};

  std::vector<unsigned int> indices = {// Front face
                                       0, 1, 2, 2, 3, 0,
                                       // Back face
                                       4, 5, 6, 6, 7, 4,
                                       // Left face
                                       8, 9, 10, 10, 11, 8,
                                       // Right face
                                       12, 13, 14, 14, 15, 12,
                                       // Top face
                                       16, 17, 18, 18, 19, 16,
                                       // Bottom face
                                       22, 21, 20, 20, 23, 22};
public:
  LightBlock(std::vector<glm::vec3> positions, glm::vec3 position) : 
    Entity(), Lightable()
  {
    setPosition(position);
    this->shader = AssetManager::getShader("lightblock");

    std::cout << "light block mesh on: " << glm::to_string(position) << std::endl;
    float r = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    std::cout << "color" << r << " " << g << " " << b << std::endl;

    this->material = new ColouredMaterial(
      glm::vec3(r,g,b),
      glm::vec3(r,g,b),
      glm::vec3(r,g,b),
      10.f
    );

    for(const auto &pos : positions){
      auto light = new lighting::PointLight(
        glm::vec3(r,g,b),
        glm::vec3(r,g,b),
        glm::vec3(r,g,b),
        pos,
        1.f, 0.09f, 0.032f
      );

      addSource(light);
    }

    this->mesh = new Mesh::InstancedMesh(vertices, indices, {}, positions, position);
    this->mesh->scale(glm::vec3{0.5f});
    this->shader->setBlockBinding("Matrices", 0);
    this->shader->setBlockBinding("DirectionalLightData", 1);
  }

  void update(float dt) override {
    
  }

  void draw() override {
    // std::cout << "drawing lightblox" << std::endl;
    // material->apply(*shader);
    // material->use();
    mesh->draw(shader);
  }
};
