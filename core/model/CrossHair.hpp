#pragma once

#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "manager/AssetManager.h"
#include "manager/WindowManager.h"
#include <iostream>
class CrossHair {
private:
  Shader *shader;
  Mesh::Mesh *mesh;
  Material *material;

public:
  CrossHair() : shader(AssetManager::getShader("basic")) {
    std::vector<Mesh::Vertex> vertices{
        // First rectangle (vertical)
        {{-0.01f, -0.5f, 0.1f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.01f, -0.5f, 0.1f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.01f, 0.5f, 0.1f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.01f, 0.5f, 0.1f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // Second rectangle (horizontal)
        {{-0.5f, -0.01f, 0.1f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.01f, 0.1f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.01f, 0.1f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.01f, 0.1f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}};

    std::vector<unsigned int> indices{
        // Indices for the first rectangle (vertical)
        0, 1, 2, 0, 2, 3,

        // Indices for the second rectangle (horizontal)
        4, 5, 6, 4, 6, 7};

    // auto width = WindowLocator::get()->getWidth();
    // auto height = WindowLocator::get()->getHeight();
    auto width = 958.f;
    auto height = 1062.f;

    std::cout << width << "x" << height << std::endl;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), 0.1f, 100.f);
    std::cout << "Projection Matrix: " << glm::to_string(projection) << std::endl;

    this->shader->use();
    this->shader->setMat4("projection", projection);

    this->material =
        new ColouredMaterial(glm::vec3{1}, glm::vec3{0.f}, glm::vec3{0.f}, 0);

    this->mesh = new Mesh::Mesh(vertices, indices, nullptr);
    this->mesh->move(glm::vec3(width / 2.f, height/ 2.f, 1.f));
    // this->mesh->move(glm::vec3{2.f, 2.f, 2.f});
    this->mesh->scale(glm::vec3(10.f));
  }

  void draw() {


    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    mesh->draw(shader);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
  }
};
