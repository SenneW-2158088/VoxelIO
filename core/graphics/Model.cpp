#include "Model.h"
#include "graphics/Shader.h"

using namespace graphics;

Model::Model(std::vector<Mesh::Mesh*> meshes, std::vector<Material*> materials)
: meshes{meshes}, materials{materials}{}

void Model::draw(Shader *shader) const {
  for(const auto& mesh : meshes) {
    mesh->draw(shader);
  }
}

Model::~Model() {
  for(auto mesh : meshes){
    delete mesh;
  }
  for(auto material : materials){
    delete material;
  }
}
