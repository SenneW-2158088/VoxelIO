#pragma once

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <glm/glm.hpp>
#include <vector>

class Material {
public:
  static const int MAX_TEXTURES = 8;

  Material() = default;
  virtual ~Material() = default;

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
  ~ColouredMaterial() = default;
  // Apply material to shader
  virtual void apply(Shader &shader) const override;
};

class TexturedMaterial : public Material {
  std::vector<Texture *> diffuse_textures;
  std::vector<Texture *> specular_textures;
  float shininess;

public:
  TexturedMaterial(std::vector<Texture *> diffuse,
                   std::vector<Texture *> specular, float shininess);
  ~TexturedMaterial() = default;
  void apply(Shader &shader) const override;
  void use() const;
};

static Material *MetalMaterial = new ColouredMaterial({}, {}, {}, .9f);
static Material *WoodMaterial = new ColouredMaterial({}, {}, {}, .9f);
