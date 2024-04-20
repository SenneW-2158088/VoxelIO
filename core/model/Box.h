#pragma once

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "model/Entity.h"

class Box : public Entity {
private:
  Shader *shader;
  Mesh::Mesh *mesh;
  TexturedMaterial *material;

  // Todo use the asset manager to load the vertices and indices
  const std::vector<Mesh::Vertex> vertices = {
      // Front face
      {{-0.5, -0.5, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
      {{0.5, -0.5, 0.5}, {0.0, 0.0, 1.0}, {1.0, 0.0}},
      {{0.5, 0.5, 0.5}, {0.0, 0.0, 1.0}, {1.0, 1.0}},
      {{-0.5, 0.5, 0.5}, {0.0, 0.0, 1.0}, {0.0, 1.0}},
      // Back face (reversed order)
      {{0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}, {0.0, 0.0}},
      {{-0.5, -0.5, -0.5}, {0.0, 0.0, -1.0}, {1.0, 0.0}},
      {{-0.5, 0.5, -0.5}, {0.0, 0.0, -1.0}, {1.0, 1.0}},
      {{0.5, 0.5, -0.5}, {0.0, 0.0, -1.0}, {0.0, 1.0}},
      // Left face
      {{-0.5, -0.5, -0.5}, {-1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{-0.5, -0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{-0.5, 0.5, 0.5}, {-1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{-0.5, 0.5, -0.5}, {-1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Right face (reversed order)
      {{0.5, -0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{0.5, -0.5, -0.5}, {1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{0.5, 0.5, -0.5}, {1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{0.5, 0.5, 0.5}, {1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Top face
      {{-0.5, 0.5, -0.5}, {0.0, 1.0, 0.0}, {0.0, 1.0}},
      {{-0.5, 0.5, 0.5}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
      {{0.5, 0.5, 0.5}, {0.0, 1.0, 0.0}, {1.0, 0.0}},
      {{0.5, 0.5, -0.5}, {0.0, 1.0, 0.0}, {1.0, 1.0}},
      // Bottom face
      {{-0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}, {1.0, 1.0}},
      {{-0.5, -0.5, 0.5}, {0.0, -1.0, 0.0}, {0.0, 1.0}},
      {{0.5, -0.5, 0.5}, {0.0, -1.0, 0.0}, {0.0, 0.0}},
      {{0.5, -0.5, -0.5}, {0.0, -1.0, 0.0}, {1.0, 0.0}}};

  std::vector<unsigned int> indices = {// Front face
                                       0, 1, 2, 2, 3, 0,
                                       // Back face
                                       4, 5, 6, 6, 7, 4,
                                       // Left face
                                       8, 9, 10, 10, 11, 8,
                                       // Right face
                                       12, 13, 14, 14, 15, 12,
                                       // Top face
                                       16, 17, 18, 18, 19, 16,
                                       // Bottom face
                                       22, 21, 20, 20, 23, 22};

public:
  Box(glm::vec3 position);
  void draw() override;
  void update(float dt) override;
};