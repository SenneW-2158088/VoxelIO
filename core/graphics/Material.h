#pragma once

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <glm/glm.hpp>

class Material {
public:
  Material() = default;
  // Apply material to shader
  virtual void apply(Shader &shader) const = 0;
};

class ColouredMaterial : public Material {
private:
  glm::vec3 ambient, diffuse, specular;
  float shininess;

public:
  ColouredMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                   float shininess);
  // Apply material to shader
  virtual void apply(Shader &shader) const override;
};

class TexturedMaterial : public Material {
  Texture &diffuse;
  Texture &specular;
  float shininess;
public:
  TexturedMaterial(Texture &diffuse, Texture &specular, float shininess);
  void apply(Shader &shader) const override;
  void use() const;
};

static Material* MetalMaterial = new ColouredMaterial({}, {}, {}, .9f);
static Material* WoodMaterial = new ColouredMaterial({}, {}, {}, .9f);
