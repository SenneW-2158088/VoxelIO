#include "Texture.h"
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

Texture::Texture(const std::string &texturePath) {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);  
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {}

void Texture::use() const {
  glActiveTexture(id);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::setTextureId(int id){
  texture = id;
}
