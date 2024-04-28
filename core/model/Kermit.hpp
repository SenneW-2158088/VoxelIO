#pragma once

#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "manager/AssetManager.h"
#include "model/Entity.h"
class Kermit : public Entity {
private:
  Shader *shader;  
  graphics::Model *model;
public:

  Kermit(glm::vec3 position) :
    shader(AssetManager::getShader("model")),
    model(AssetManager::getModel("kermit"))
  {
    this->position = position;
    this->shader->setBlockBinding("Matrices", 0);
    this->shader->setBlockBinding("DirectionalLightData", 1);
  }

  void draw() override {
     model->draw(shader);
  }

  void update(float dt) override {
    
  }

};
