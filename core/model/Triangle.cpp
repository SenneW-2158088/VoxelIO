//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Triangle.h"
#include "manager/AssetManager.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Triangle::Triangle() : shader{AssetManager::getShader("default")}
    {
        const std::vector<Mesh::Vertex> vertices = {
                {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}
        };

        const std::vector<unsigned int> indices = {0, 1, 2};

        mesh = new Mesh::Mesh(vertices, indices, {});

        position = glm::vec3{0.0f, 0.0f, 0.0f};
}

void Triangle::draw() {
    mesh->draw(shader);
}

void Triangle::update(float dt) {
    // Do nothing
}