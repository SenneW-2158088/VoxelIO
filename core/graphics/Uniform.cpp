//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Uniform.h"
#include "game/Game.h"
#include <exception>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Uniform::GameUniform::GameUniform(glm::mat4 projection, glm::mat4 view, glm::vec4 viewPos) :
        projection(projection),
        view(view),
        viewPos(viewPos) {

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2 + sizeof(glm::vec4), 0, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, NULL, sizeof(glm::mat4) * 2 + sizeof(glm::vec4));

    setProjection(projection);
    setView(view);
    setViewPos(viewPos);
}

Uniform::GameUniform::~GameUniform() {
    std::cout << "Destroying GameUniform" << std::endl;
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

void Uniform::GameUniform::setViewPos(glm::vec4 viewPos) {
    this->viewPos = viewPos;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, sizeof(glm::vec4),
                    glm::value_ptr(this->viewPos));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Uniform::GameUniform *UniformLocator::uniform = nullptr;

void UniformLocator::provide(Uniform::GameUniform* uniform){
    Uniform::GameUniform* gameUniform = uniform;
    if (!gameUniform){
        // Todo implement null uniform class
    }

    UniformLocator::uniform = gameUniform;

}

Uniform::GameUniform* UniformLocator::get(){
    return uniform;
}
