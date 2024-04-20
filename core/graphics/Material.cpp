#include "Material.h"
#include <iostream>

ColouredMaterial::ColouredMaterial(glm::vec3 ambient, glm::vec3 diffuse,
                                   glm::vec3 specular, float shininess)
    : ambient{ambient}, diffuse{diffuse}, specular{specular}, shininess{
                                                                  shininess} {}

void ColouredMaterial::apply(Shader &shader) const {
  shader.use();
  shader.setVec3("material.ambient", ambient);
  shader.setVec3("material.diffuse", diffuse);
  shader.setVec3("material.specular", specular);
  shader.setFloat("material.shininess", shininess);
}

TexturedMaterial::TexturedMaterial(Texture &diffuse, Texture &specular, float shininess)
    : diffuse{diffuse}, specular{specular}, shininess{shininess} {}

void TexturedMaterial::apply(Shader &shader) const {
  shader.use();
  shader.setInt("material.diffuse", diffuse.getId());
  std::cout << "binded material.diffuse to texture " << diffuse.getId() << std::endl;
  shader.setInt("material.specular", specular.getId());
  std::cout << "binded material.specular to texture " << specular.getId() << std::endl;
  shader.setFloat("material.shininess", shininess);
}

void TexturedMaterial::use() const {
  diffuse.use();
  specular.use();
}
