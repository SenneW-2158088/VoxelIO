#pragma once

#include <vector>

#include <graphics/Mesh.h>

namespace graphics {

class Model {
  private:  
    std::vector<Mesh::Mesh*> meshes;
  public:
    Model();
    ~Model();
};

}
