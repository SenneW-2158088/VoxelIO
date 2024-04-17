#pragma once

#include "graphics/Cubemap.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "model/Entity.h"

class Skybox : public Entity { 
private:
  Mesh::Mesh* mesh;
  Shader* shader;
  Cubemap* cubemap;

  // Todo use the asset manager to load the vertices and indices
  const std::vector<Mesh::Vertex> vertices = {
      // Front face
      {{-1.f, -1.f, 1.f}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
      {{1.f, -1.f, 1.f}, {0.0, 0.0, 1.0}, {1.0, 0.0}},
      {{1.f, 1.f, 1.f}, {0.0, 0.0, 1.0}, {1.0, 1.0}},
      {{-1.f, 1.f, 1.f}, {0.0, 0.0, 1.0}, {0.0, 1.0}},
      // Back face (reversed order)
      {{1.f, -1.f, -1.f}, {0.0, 0.0, -1.0}, {0.0, 0.0}},
      {{-1.f, -1.f, -1.f}, {0.0, 0.0, -1.0}, {1.0, 0.0}},
      {{-1.f, 1.f, -1.f}, {0.0, 0.0, -1.0}, {1.0, 1.0}},
      {{1.f, 1.f, -1.f}, {0.0, 0.0, -1.0}, {0.0, 1.0}},
      // Left face
      {{-1.f, -1.f, -1.f}, {-1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{-1.f, -1.f, 1.f}, {-1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{-1.f, 1.f, 1.f}, {-1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{-1.f, 1.f, -1.f}, {-1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Right face (reversed order)
      {{1.f, -1.f, 1.f}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
      {{1.f, -1.f, -1.f}, {1.0, 0.0, 0.0}, {1.0, 0.0}},
      {{1.f, 1.f, -1.f}, {1.0, 0.0, 0.0}, {1.0, 1.0}},
      {{1.f, 1.f, 1.f}, {1.0, 0.0, 0.0}, {0.0, 1.0}},
      // Top face
      {{-1.f, 1.f, -1.f}, {0.0, 1.0, 0.0}, {0.0, 1.0}},
      {{-1.f, 1.f, 1.f}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
      {{1.f, 1.f, 1.f}, {0.0, 1.0, 0.0}, {1.0, 0.0}},
      {{1.f, 1.f, -1.f}, {0.0, 1.0, 0.0}, {1.0, 1.0}},
      // Bottom face
      {{-1.f, -1.f, -1.f}, {0.0, -1.0, 0.0}, {1.0, 1.0}},
      {{-1.f, -1.f, 1.f}, {0.0, -1.0, 0.0}, {0.0, 1.0}},
      {{1.f, -1.f, 1.f}, {0.0, -1.0, 0.0}, {0.0, 0.0}},
      {{1.f, -1.f, -1.f}, {0.0, -1.0, 0.0}, {1.0, 0.0}}};

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
  Skybox();
  void draw() override;
  void update(float dt) override;
};
