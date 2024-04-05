#pragma once

#include <string>
class Texture {
private:
  unsigned int id;
  unsigned int texture;

public:
  [[nodiscard]] inline unsigned int getTexture() const { return texture; };
  [[nodiscard]] inline unsigned int getId() const { return id; };

public:
  void setTextureId(int id);

public:
  Texture(const std::string &texturePath);
  ~Texture();
  void use() const;
};
