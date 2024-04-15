/*
  Interface for adding and drawing terrains to the engine
*/
#pragma once

#include <glm/glm.hpp>

class Terrain {
protected:
  glm::vec3 base_position; // used to render chunks
public:
  inline void setBasePosition(const glm::vec3 position) {
    base_position = position;
  };

public:
  virtual void draw() const = 0;
  virtual void update(const float dt) {};
};
