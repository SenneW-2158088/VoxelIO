#include "Texture.h"
#include "graphics/Shader.h"
#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const std::string &texturePath, Format format) : id{GL_TEXTURE0}{
  glGenTextures(1, &texture);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(false);
  unsigned char *data =
      stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
  
  // unsigned int gl_format = (format == Format::PNG) ? GL_RGBA : GL_RGB;

  GLenum gl_format;
  if (nrChannels == 1) gl_format = GL_RED;
  else if (nrChannels == 3) gl_format = GL_RGB;
  else if (nrChannels == 4) gl_format = GL_RGBA;


  if (data) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  } else {
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);
}

Texture::~Texture() {}

void Texture::use() const {
  glActiveTexture(id);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::setTextureId(int id) { this->id = id; }

void Texture::apply(Shader &shader) const {
  shader.setInt("texture", id);
}
