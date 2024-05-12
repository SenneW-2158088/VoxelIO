//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_VOXEL_H
#define VOXELIO_VOXEL_H

#include "gameplay/Collision.h"
#include "glm/fwd.hpp"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Texture.h"
#include <graphics/Mesh.h>
#include <graphics/Shader.h>
#include <model/Entity.h>
#include <optional>
#include <vector>
#include <iostream>

class Voxel : public Entity, public Collision::Collisionable {
private:
  Shader *shader;
  Mesh::Mesh *mesh;
  Texture *texture;

  bool isHighlighted = false;

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
  Voxel(glm::vec3 position);

  void update(float dt) override;

  void draw() override;

  inline void highlight() { isHighlighted = true;};

  void onCollide(const Collision::Collisioner &own, const Collision::Collisioner &other) override;
};

class InstancedVoxel : public Entity, public Collision::Collisionable {
private:
  Shader *shader;
  Mesh::InstancedMesh* mesh;
  Texture *texture;
  Collision::CollisionerOctree* tree;
  std::vector<glm::vec3> positions;

  std::optional<unsigned int> highlighted;

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
  void tempCollide(const Collision::Collisioner& own, const Collision::Collisioner & other);

  int getIndex(glm::vec3 position){
    auto it = find(positions.begin(), positions.end(), position); 
    if (it != positions.end())  
    { 
        return it - positions.begin(); 
    }else{
      return -1;
    }
  }

public:
  inline void highlight(glm::vec3 position) {
    auto index =getIndex(position);
    if (index != -1)  
    { 
        highlighted = index;
    }else{
      highlighted = std::nullopt;
    }
  };
  InstancedVoxel(std::vector<glm::vec3> positions, glm::vec3 position);
  void draw() override;
  void update(float dt) override;
  void collide(Collisionable &other) override;
  void onCollide(const Collision::Collisioner &own, const Collision::Collisioner &other) override;
  void destroy(glm::vec3 position);
};
#endif // VOXELIO_VOXEL_H
