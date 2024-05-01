#include "Material.h"
#include "glad/glad.h"
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

TexturedMaterial::TexturedMaterial(std::vector<Texture*> diffuse, std::vector<Texture*> specular, float shininess)
    : diffuse_textures{diffuse}, specular_textures{specular}, shininess{shininess} {

      for(int i = 0; i < diffuse.size() && i < MAX_TEXTURES; i++){
        // std::cout << "settings diffuse id: " << i << std::endl;
        diffuse_textures[i]->setTextureId(GL_TEXTURE0 + i);
      }

      for(int i = 0; i < specular.size() && i < MAX_TEXTURES; i++){
        // std::cout << "settings specular id: " << i + diffuse_textures.size() << std::endl;
        specular_textures[i]->setTextureId(GL_TEXTURE0 + i + diffuse_textures.size());
      }
    }

void TexturedMaterial::apply(Shader &shader) const {
  shader.use();

  for(unsigned int i = 0; i < diffuse_textures.size(); i++){
    std::string name = "material.diffuse_textures[" + std::to_string(i) + "]";
    // std::cout << "added: " << name << " binded to texture "<< diffuse_textures[i]->getId() << std::endl;
    shader.setInt(name, diffuse_textures[i]->getId());
  }

  shader.setInt("material.diffuse_texture_count", diffuse_textures.size());

  for(unsigned int i = 0; i < specular_textures.size(); i++){
    std::string name = "material.specular_textures[" + std::to_string(i) + "]";
    // std::cout << "added: " << name << " binded to texture "<< specular_textures[i]->getId() << std::endl;
    shader.setInt(name, specular_textures[i]->getId());
  }

  shader.setInt("material.specular_texture_count", specular_textures.size());

  shader.setFloat("material.shininess", shininess);
}

void TexturedMaterial::use() const {
  for(const auto& diffuse : diffuse_textures){
    diffuse->use();
  }
  for(const auto& specular: specular_textures){
    specular->use();
  }
}
