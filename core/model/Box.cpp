#include "Box.h"
#include "glad/glad.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "manager/AssetManager.h"

Box::Box(glm::vec3 position) : shader{AssetManager::getShader("box")} {
  this->position = position;

  this->mesh = new Mesh::Mesh(vertices, indices, {});
  this->mesh->move(this->position);
  this->mesh->scale(glm::vec3{1.f});

  // this->material = new ColouredMaterial{
  //   {1, 1, 1},
  //   {1, 1, 1},
  //   {1, 1, 1},
  //   1.0
  // };

  Texture* diffuse = AssetManager::getTexture("box.png");
  diffuse->setTextureId(GL_TEXTURE0);

  Texture* specular = AssetManager::getTexture("box-specular.png");
  specular->setTextureId(GL_TEXTURE1);

  this->material = new TexturedMaterial{
    *diffuse,
    *specular,
    32.0
  };

  this->material->apply(*shader);

}

void Box::draw() {
  material->use();
  mesh->draw(shader);
}

void Box::update(float dt) {
  
}
