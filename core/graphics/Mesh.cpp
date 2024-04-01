//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Mesh.h"
#include <glad/glad.h>

Mesh::BaseMesh::BaseMesh() {
    this->VAO = 0;
    this->VBO = 0;
}

Mesh::BaseMesh::BaseMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                         std::vector<unsigned int> textures) :
        vertices(vertices), indices(indices), textures(textures) {
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

    // Calculate stride
    const unsigned int stride = sizeof(Vertex);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*) offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*) offsetof(Vertex, uv));

    // Unbind VAO
    glBindVertexArray(0);
}

void Mesh::BaseMesh::draw(Shader &shader) {
    // Bind VAO
    glBindVertexArray(VAO);

    //TODO: Implement texture loading

    // Draw elements
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind VAO
    glBindVertexArray(0);

}

void Mesh::BaseMesh::move(glm::vec3 position) {

}

void Mesh::BaseMesh::rotate() {

}

void Mesh::BaseMesh::scale() {

}


Mesh::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures,
                 glm::vec3 size, glm::vec3 position) : BaseMesh{vertices, indices, textures}, size(size), position(position) {}
Mesh::InstancedMesh::InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                                   std::vector<unsigned int> textures, std::vector<glm::vec3> positions) : BaseMesh{vertices, indices, textures}, positions{positions}{}