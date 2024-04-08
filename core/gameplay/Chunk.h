#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <vector>

// Very basic shitty chunk with individual voxels
class Chunk : Entity {
private:
  std::vector<Voxel> voxels;
  const unsigned int chunk_size = 16; // 16^3 blocks per chunk

public:
  Chunk();
  void draw() override;
};
