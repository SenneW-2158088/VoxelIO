//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_UNIFORM_H
#define VOXELIO_UNIFORM_H

#include "graphics/Lighting.h"
#include <glm/glm.hpp>

namespace Uniform {

class BaseUniform {
protected:
  unsigned int UBO;
};

class GameUniform : public BaseUniform {
private:
  glm::mat4 projection;
  glm::mat4 view;
  glm::vec4 viewPos;

public:
public:
  GameUniform(glm::mat4 projection, glm::mat4 view, glm::vec4 viewPos);
  ~GameUniform();

  inline glm::mat4 getProjection() const { return projection; }

  inline glm::mat4 getView() const { return view; }

  inline glm::vec4 getViewPos() const { return viewPos; }

public:
  void setProjection(glm::mat4 projection);

  void setView(glm::mat4 view);

  void setViewPos(glm::vec4 viewPos);
};
class LightingUniform : public Uniform::BaseUniform {
private:
  bool active;
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
  glm::vec4 direction;

public:
  void setActive(bool active);
  void setAmbient(glm::vec3 ambient);
  void setDiffuse(glm::vec3 diffuse);
  void setSpecular(glm::vec3 specular);
  void setDirection(glm::vec3 direction);
public:
  LightingUniform(lighting::DirectionalLight light);
  ~LightingUniform();
  void setDirectionalLight(lighting::DirectionalLight light);
};

} // namespace Uniform

// a Static service for locating uniforms
class UniformLocator {
private:
  static Uniform::GameUniform *gameUniform;
  static Uniform::LightingUniform *lightingUniform;

  public : UniformLocator() = delete;

  static void provideGame(Uniform::GameUniform *uniform);
  static void provideLighting(Uniform::LightingUniform *uniform);
  static Uniform::GameUniform *getGame();
  static Uniform::LightingUniform* getLighting();
};

#endif // VOXELIO_UNIFORM_H
