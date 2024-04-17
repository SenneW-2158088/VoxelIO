#pragma once

#include <string>
#include <vector>

class Cubemap {
private:
  unsigned int id;
  unsigned int texture;

public:
  [[nodiscard]] inline unsigned int getTexture() const {return texture;};
  [[nodiscard]] inline unsigned int getId() const { return id; };
public:
  void setTextureId(int id);
public:
  Cubemap(std::vector<std::string> &faces);
  ~Cubemap();

  void use() const;
};
