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

void Model::move(const glm::vec3 position){
  for(auto mesh : meshes){
    mesh->move(position);
  }
}

void Model::scale(const glm::vec3 scale) {
  for(auto mesh : meshes){
    mesh->scale(scale);
  }
}

void Model::scaleToWorld(const glm::vec3 scale) {
  for(auto mesh : meshes){
    mesh->scaleToWorld(scale);
  }
}

void Model::rotate(const float rotation, const glm::vec3 axis) {
  for(auto mesh : meshes){
    mesh->rotate(rotation, axis);
  }
}
