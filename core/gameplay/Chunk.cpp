#include "Chunk.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <iostream>
#include <algorithm>

#include <gameplay/Noise.h>

BasicChunk::BasicChunk(const noise::Noise &noise) : Chunk{}, voxels() {

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


InstancedChunk::InstancedChunk(const noise::Noise &noise, glm::vec3 position){
  std::vector<glm::vec3> positions{};
  unsigned int const size = 16;

  // generating positions
  for (int x = 0; x < size; x++) {
    for (int z = 0; z < size; z++) {
      // base layers
      auto height = std::max(noise.noise((position.x + x) * .005, (position.z + z)* .005), -1.0);
      height += std::max(noise.noise((position.x + x) * .001, (position.z + z)* .001), -1.0);

      // mountain layers
      // height += noise.noise((position.x + x) * .05, (position.z + z)* .05);
      // height += noise.noise((position.x + x) * .05, (position.z + z)* .05);
      height += noise.noise((position.x + x) * .02, (position.z + z)* .02);
      height += noise.noise((position.x + x) * .01, (position.z + z)* .01);
      // std::cout << height << std::endl; // value between -1 and 1

      for (int y = 0; y < base + floor(size * height); y++) {
       // std::cout << "Created voxel on: " << glm::to_string(glm::vec3{x, y, z}) << std::endl;
        positions.push_back(glm::vec3{x,y,z});
      }
    }
  }

  this->positions = positions;

  // creating instanced voxel
  this->voxels = new InstancedVoxel(positions, position);
}

void InstancedChunk::draw() const {
    this->voxels->draw();
}

glm::vec3 InstancedChunk::getSpawnPos(glm::vec3 position) {
  return glm::vec3(position.x, voxels->getHeight(position), position.z);
}

