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
    void draw(Shader *shader) const;
    
    ~Model();
};

}
