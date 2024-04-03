//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"

#include <manager/AssetManager.h>
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Voxel::Voxel() :
        mesh{new Mesh::Mesh(vertices, indices, {})},
        shader{AssetManager::getShader("basic")} {

//    this->shader->setBlockBinding("Matrices", 0);
    this->position = glm::vec3{0.0f, 0.0f, 0.0f};
}

void Voxel::update(float dt) {

}

void Voxel::draw() {
    //TODO refactor hardcoded values
//    glm::mat4 model = glm::mat4 {1.f};
//    model = glm::scale(model, glm::vec3{5.0f});
//    model = glm::translate(model, this->position);
//
//    shader->setMat4("model", model);
    mesh->draw(shader);
}