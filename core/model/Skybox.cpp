#include "Skybox.h"
#include "glad/glad.h"

#include <manager/AssetManager.h>

Skybox::Skybox() :
  shader{AssetManager::getShader("cubemap")},
  cubemap{AssetManager::getCubemap("basic")}
{
  this->mesh = new Mesh::Mesh{vertices, indices, {}};
  this->shader->setBlockBinding("Matrices", 0);
}

void Skybox::draw(){
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_FALSE);

  cubemap->use();
  mesh->draw(shader);

  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
}

void Skybox::update(float dt){
  
}
