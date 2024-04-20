#pragma once

#include "graphics/Shader.h"
#include <string>
class Texture {
private:
  unsigned int id;
  unsigned int texture;

public:
  enum class Format {
    PNG,
    JPG
  };
public:
  [[nodiscard]] inline unsigned int getTexture() const { return texture; };
  [[nodiscard]] inline unsigned int getId() const { return id - 0x84C0; };

public:
  void setTextureId(int id);

public:
  Texture(const std::string &texturePath, Format format);
  ~Texture();

  void apply(Shader &shader) const;
  void use() const;
};
