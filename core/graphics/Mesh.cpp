//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Mesh.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <utility>

Mesh::BaseMesh::BaseMesh(std::vector<Vertex> vertices,
                         std::vector<unsigned int> indices,
                         Material* material)
    : vertices(vertices), indices(indices), material(material), model{1.f}, translation{0.f} {
  // Bind VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Bind VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               &this->vertices[0], GL_DYNAMIC_DRAW);

  // Bind IBO
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &this->indices[0], GL_DYNAMIC_DRAW);

  // Calculate stride
  const unsigned int stride = sizeof(Vertex);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)nullptr);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
                        (void *)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
                        (void *)offsetof(Vertex, uv));

  // Unbind VAO
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // calculate base translation
  for(const auto &v : vertices){
    translation = glm::min(translation, v.position);
  }

  model = glm::translate(model, -translation);
}

void Mesh::BaseMesh::draw(Shader *shader) {

  if(material){
    material->apply(*shader);
    material->use();
  }

  shader->use();
  shader->setMat4("model", model);

  // Bind buffers
  glBindVertexArray(VAO);

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

std::pair<glm::vec3, glm::vec3> getMeshMinMax(Mesh::BaseMesh* mesh){
  glm::vec3 min{0}, max{0};

  for(const auto& vertex : mesh->getVertices()){
    min = glm::min(min, vertex.position);
    max = glm::max(max, vertex.position);
  }

  return std::pair{min, max};
}

glm::vec3 getMeshSize(Mesh::BaseMesh* mesh){
  auto minMax = getMeshMinMax(mesh);
  return minMax.second - minMax.first;
}

void Mesh::BaseMesh::scaleToWorld(const glm::vec3 scale) {
  model = glm::scale(model, scale / getMeshSize(this));
}

Mesh::Mesh::Mesh(std::vector<Vertex> vertices,
                 std::vector<unsigned int> indices,
                 Material* material)
    : BaseMesh{vertices, indices, material} {}

Mesh::InstancedMesh::InstancedMesh(std::vector<Vertex> vertices,
                                   std::vector<unsigned int> indices,
                                   Material* material,
                                   std::vector<glm::vec3> positions, glm::vec3 position)
    : BaseMesh{vertices, indices, material} {
  // Bind vertex array
  glBindVertexArray(VAO);

  std::cout << "in constructor" << std::endl;

  // Initialize model matrices
  for(const auto &pos : positions){
    glm::mat4 model{1.f};
    models.push_back(glm::translate(this->model, position + pos));
    active.push_back(true);
  }

  std::cout << "creating vbo" << std::endl;

  // Initialize instance VBO
  glGenBuffers(1, &VBO_INSTANCED);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_INSTANCED);
  glBufferData(GL_ARRAY_BUFFER, this->models.size() * sizeof(glm::mat4),
               &this->models[0], GL_STATIC_DRAW);

 

  std::cout << "applying stride" << std::endl;
  // Calculate stride, mat4 = 4 * vec4
  const auto stride = sizeof(glm::vec4) * 4;

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride, (void *)nullptr);

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, stride,
                        (void *)sizeof(glm::vec4));

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, stride,
                        (void *)(sizeof(glm::vec4) * 2));

  glEnableVertexAttribArray(6);
  glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, stride,
                        (void *)(sizeof(glm::vec4) * 3));

  std::cout << "add divisor" << std::endl;
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  glVertexAttribDivisor(6, 1);

  std::cout << "unbind" << std::endl;
  // unbind VBO_INSTANCED
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  for(auto i : active){
    std::cout << i << std::endl;
  }

  glGenBuffers(1, &ACTIVE_BUFFER);
  glBindBuffer(GL_ARRAY_BUFFER, ACTIVE_BUFFER);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->active.size(), this->active.data(), GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(7); // Assuming 7 is the next available index
  glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*) nullptr);
  glVertexAttribDivisor(7, 1);  // Important for instancing

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // unbind VAO
  glBindVertexArray(0);
}
void Mesh::InstancedMesh::draw(Shader *shader) {

  if(material){
    material->apply(*shader);
    material->use();
  }

  shader->use();
  shader->setMat4("model", model);

  // Bind buffers
  glBindVertexArray(VAO);

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
  glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr, this->models.size());

  // Unbind buffers
  glBindVertexArray(0);
}

void Mesh::InstancedMesh::move(const glm::vec3 position) {
  for(int i = 0; i < models.size(); i++) {
    models[i] = glm::translate(models[i], position);
  }
}

void Mesh::InstancedMesh::setActive(int index, bool value){
  if (index >= 0 && index < active.size()) {
        active[index] = value ? 1.0f : 0.0f;
        glBindBuffer(GL_ARRAY_BUFFER, ACTIVE_BUFFER);
        glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(float), sizeof(float), &active[index]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
