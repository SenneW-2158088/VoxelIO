#include "Material.h"

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
  shader.setInt("material.diffuse", 0);
  shader.setInt("material.specular", 1);
  shader.setFloat("material.shininess", shininess);
}

void TexturedMaterial::use() const {
  diffuse.use();
  specular.use();
}
