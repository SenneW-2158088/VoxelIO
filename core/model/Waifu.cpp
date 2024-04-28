#include "Waifu.h"
#include "manager/AssetManager.h"

Waifu::Waifu(glm::vec3 position):
shader{AssetManager::getShader("model")},
model{AssetManager::getModel("mandy")}
 {
  this->position = position;

  this->shader->setBlockBinding("Matrices", 0);
  this->shader->setBlockBinding("DirectionalLightData", 1);
}

void Waifu::draw(){
  model->draw(shader);
}

void Waifu::update(float dt){
  
}
