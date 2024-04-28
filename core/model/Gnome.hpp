#pragma once

#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "manager/AssetManager.h"
#include "model/Entity.h"

class Gnome : public Entity {
private:
  Shader *shader;  
  graphics::Model *model;
public:
  Gnome(glm::vec3 position) :
    shader(AssetManager::getShader("model")),
    model(AssetManager::getModel("gnomie"))
  {
    this->position = position;
    this->shader->setBlockBinding("Matrices", 0);
    this->shader->setBlockBinding("DirectionalLightData", 1);

    this->model->scaleToWorld(glm::vec3{1.8f});
  }

  void draw() override {
     model->draw(shader);
  }

  void update(float dt) override {
    
  }

};
