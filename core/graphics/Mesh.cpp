//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Mesh.h"
#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Mesh::BaseMesh::BaseMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                         std::vector<unsigned int> textures) :
        vertices(vertices), indices(indices), textures(textures), model{1.f} {
    // Bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &this->vertices[0], GL_DYNAMIC_DRAW);

    // Bind IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &this->indices[0], GL_DYNAMIC_DRAW);

    // Calculate stride
    const unsigned int stride = sizeof(Vertex);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *) offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *) offsetof(Vertex, uv));

    // Unbind VAO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::BaseMesh::draw(Shader *shader) {

    shader->use();
//    shader->setBlockBinding("Matrices", 0);
    shader->setMat4("model", model);

    // Bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);



    // Validate program
    int success;
    char infoLog[512];
    glValidateProgram(shader->getProgram());
    glGetProgramiv(shader->getProgram(), GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader->getProgram(), 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
    }

    // Draw elements
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::BaseMesh::move(glm::vec3 position) {
    model = glm::translate(model, position);
}

void Mesh::BaseMesh::rotate(const float rotation, const glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(90.f), axis);
}

void Mesh::BaseMesh::scale(const glm::vec3 scale) {
    model = glm::scale(model, scale);
}


Mesh::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures) : BaseMesh{vertices, indices, textures}{}

Mesh::InstancedMesh::InstancedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                                   std::vector<unsigned int> textures) : BaseMesh{vertices, indices,
                                                                                textures}{}