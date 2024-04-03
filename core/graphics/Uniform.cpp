//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Uniform.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Uniform::GameUniform::GameUniform(glm::mat4 projection, glm::mat4 view, glm::vec3 viewPos) :
        projection(projection),
        view(view),
        viewPos(viewPos) {

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2 + sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, NULL, sizeof(glm::mat4) * 2 + sizeof(glm::vec3));

    setProjection(projection);
    setView(view);
    setViewPos(viewPos);
}

Uniform::GameUniform::~GameUniform() {
    glDeleteBuffers(1, &UBO);
}

void Uniform::GameUniform::setProjection(glm::mat4 projection) {
    this->projection = projection;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(this->projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::GameUniform::setView(glm::mat4 view) {
    this->view = view;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(this->view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::GameUniform::setViewPos(glm::vec3 viewPos) {
    this->viewPos = viewPos;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, sizeof(glm::vec3),
                    glm::value_ptr(this->viewPos));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}