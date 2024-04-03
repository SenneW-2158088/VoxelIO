//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"

#include <manager/AssetManager.h>
#include <iostream>

Voxel::Voxel() :
        shader{AssetManager::getShader("default")} {

    this->mesh = new Mesh::Mesh(vertices, indices, {});
    this->shader->setBlockBinding("Matrices", 0);
    this->position = glm::vec3{0.0f, 0.0f, 10.0f};
}

void Voxel::update(float dt) {

}

void Voxel::draw() {
    mesh->draw(shader);
}