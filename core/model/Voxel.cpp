//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Voxel.h"

#include <manager/AssetManager.h>
#include <vector>

Voxel::Voxel() :
        mesh{new Mesh::Mesh(vertices, indices, std::vector<unsigned int>{}, glm::vec3{1.0f}, glm::vec3{0.0f})},
        shader{AssetManager::getShader("default")} {

}

void Voxel::update(float dt) {

}

void Voxel::draw() {
    mesh->draw(*shader);
}