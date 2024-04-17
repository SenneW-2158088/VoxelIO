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
  inline void setTextureId(int id) { this->id = id; };
public:
  Cubemap(std::vector<std::string> &faces);
  ~Cubemap() = default;

  void use() const;
};
