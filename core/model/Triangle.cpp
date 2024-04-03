//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Triangle.h"
#include "manager/AssetManager.h"
#include <glad/glad.h>

Triangle::Triangle() : shader{AssetManager::getShader("basic")} {
    // Todo use the asset manager to load the vertices and indices
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Mesh::Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *) 0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *) offsetof(Mesh::Vertex, normal));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *) offsetof(Mesh::Vertex, uv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Triangle::draw() {
    shader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Triangle::update(float dt) {
    // Do nothing
}