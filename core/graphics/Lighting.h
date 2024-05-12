#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace lighting {
// Basic lighting class
class Light {
protected:
  bool active = false;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

public:
  Light();
  Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
  virtual ~Light(){ };

  inline void setActive(bool active) { this->active = active; };
  inline void toggle() { this->active = !active; };
public:
  inline bool isActive() const { return active; };
  inline glm::vec3 getAmbient() const {return ambient; };
  inline glm::vec3 getDiffuse() const {return diffuse; };
  inline glm::vec3 getSpecular() const {return specular; };
};

class DirectionalLight : public Light {
protected:
  glm::vec3 direction;
public:
  DirectionalLight();
  DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
public:
  inline glm::vec3 getDirection() const {return direction; };
};

class PointLight : public Light {
protected:
  glm::vec3 position;

  float constant;
  float linear;
  float quadratic;
public:
  PointLight();
  PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic);
  glm::vec3 getPosition() { return this->position; }
  glm::vec3 getDistance() { return glm::vec3{constant,linear, quadratic}; };
};

class SpotLight : public PointLight {
protected:
  glm::vec3 direction;
  float cutOff;
};
} // namespace lighting

/* Interface for entities that are a light */
class Lightable {
private:
  std::vector<lighting::Light *> sources;

public:
  Lightable() = default;
  inline std::vector<lighting::Light *>getSources() const { return sources; };
  inline void addSource(lighting::Light* source) {this->sources.push_back(source);}
};
