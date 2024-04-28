#pragma once

#include "graphics/Material.h"
#include <vector>

#include <graphics/Mesh.h>

namespace graphics {

class Model {
  private:  
    std::vector<Mesh::Mesh*> meshes;
    std::vector<Material*> materials;
  public:
    Model(std::vector<Mesh::Mesh*> meshes, std::vector<Material*> materials);
    void move(const glm::vec3 position);
    void rotate(const float rotation, const glm::vec3 axis);
    void scale(const glm::vec3 scale);
    void scaleToWorld(const glm::vec3 scale);
    void draw(Shader *shader) const;
    ~Model();
};

}
