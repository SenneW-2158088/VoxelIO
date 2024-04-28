#pragma once

#include "graphics/Model.h"
#include "graphics/Shader.h"
#include "model/Entity.h"
class Waifu : public Entity {
private:
  Shader *shader;
  graphics::Model* model;
public:
  Waifu(glm::vec3 position);
  void draw() override;
  void update(float dt) override;
};
