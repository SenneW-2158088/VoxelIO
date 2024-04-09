#include "Chunk.h"
#include "gameplay/Collision.h"
#include "glm/gtx/string_cast.hpp"
#include "graphics/Mesh.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <iostream>

#include <gameplay/Noise.h>

BasicChunk::BasicChunk() : Chunk{}, voxels() {
  unsigned int const size = 16;
  auto noise = Noise::Perlin();

  std::cout << "Creating basic chunk" << std::endl;

  for (int x = 0; x < size; x++) {
    for (int z = 0; z < size; z++) {
      const auto height = noise.noise(x * .05, z * .05);
      std::cout << height << std::endl; // value between -1 and 1

      for (int y = 0; y < floor(height * size); y++) {
        // std::cout << "Created voxel on: " << glm::to_string(glm::vec3{x, y, z})
                  // << std::endl;
        const auto v = new Voxel(glm::vec3{x, y, z});
        voxels.push_back(v);
      }
    }
  }
}

void BasicChunk::draw() const {
  for (const auto &v : voxels) {
    v->draw();
  }
}


InstancedChunk::InstancedChunk(){
  std::vector<glm::vec3> positions{};
  unsigned int const size = 16;
  auto noise = Noise::Perlin();

  // generating positions
  for (int x = 0; x < size; x++) {
    for (int z = 0; z < size; z++) {
      const auto height = noise.noise(x * .05, z * .05);
      std::cout << height << std::endl; // value between -1 and 1

      for (int y = 0; y < floor(height * size); y++) {
        // std::cout << "Created voxel on: " << glm::to_string(glm::vec3{x, y, z}) << std::endl;
        const auto v = new Voxel(glm::vec3{x, y, z});
        positions.push_back(glm::vec3{x,y,z});
      }
    }
  }

  // creating instanced voxel
  this->voxels = new InstancedVoxel(positions);
}

void InstancedChunk::draw() const {
    this->voxels->draw();
}
