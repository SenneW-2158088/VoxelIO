//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "Uniform.h"
#include "game/Game.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Lighting.h"
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

Uniform::LightingUniform::LightingUniform(lighting::DirectionalLight light){
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);

    const unsigned int size = sizeof(int) + sizeof(glm::vec4) * 4;

    glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STATIC_DRAW);
    // glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Bind buffer to shader layout 1
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, UBO);

    setActive(light.isActive());
    setAmbient(light.getAmbient());
    setDiffuse(light.getDiffuse());
    setSpecular(light.getSpecular());
    setDirection(light.getDirection());
}

Uniform::LightingUniform::~LightingUniform() {
    std::cout << "Destroying LightinUniform" << std::endl;
    glDeleteBuffers(1, &UBO);
}

void Uniform::LightingUniform::setActive(bool active) {
    this->active = (int) active;
    std::cout << "Uniform active: " << this->active << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 4, sizeof(int), &this->active);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::LightingUniform::setAmbient(glm::vec3 ambient) {
    this->ambient = glm::vec4{ambient, 1.f};
    std::cout << "Uniform ambient: " << glm::to_string(this->ambient) << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(this->ambient));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::LightingUniform::setDiffuse(glm::vec3 diffuse) {
    this->diffuse= glm::vec4{diffuse, 1.f};
    std::cout << "Uniform diffuse: " << glm::to_string(this->diffuse) << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(this->diffuse));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::LightingUniform::setSpecular(glm::vec3 specular) {
    this->specular= glm::vec4{specular, 1.f};
    std::cout << "Uniform specular: " << glm::to_string(this->specular) << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec4), glm::value_ptr(this->specular));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Uniform::LightingUniform::setDirection(glm::vec3 direction) {
    this->direction= glm::vec4{direction, 1.f};
    std::cout << "Uniform direction: " << glm::to_string(this->direction) << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 3, sizeof(glm::vec4), glm::value_ptr(this->direction));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

// Static uniform objects
Uniform::GameUniform *UniformLocator::gameUniform = nullptr;
Uniform::LightingUniform *UniformLocator::lightingUniform = nullptr;

void UniformLocator::provideGame(Uniform::GameUniform* uniform){
    Uniform::GameUniform* gameUniform = uniform;
    if (!gameUniform){
        // Todo implement null uniform class
    }

    UniformLocator::gameUniform = gameUniform;

}

void UniformLocator::provideLighting(Uniform::LightingUniform* uniform) {
    Uniform::LightingUniform* lightingUniform = uniform;
    if (!lightingUniform){
        // Todo implement null uniform class
    }

    UniformLocator::lightingUniform= lightingUniform;
}

Uniform::GameUniform* UniformLocator::getGame(){
    return gameUniform;
}

Uniform::LightingUniform* UniformLocator::getLighting(){
    return lightingUniform;
}
