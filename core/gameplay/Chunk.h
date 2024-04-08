#pragma once

#include "graphics/Mesh.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <vector>

// Very basic shitty chunk with individual voxels
class Chunk {
private:
public:
  Chunk() = default;
  virtual void draw() const = 0;
};

class BasicChunk : public Chunk {
private:
  std::vector<Voxel*> voxels;
public:
  BasicChunk();
  void draw() const override;
};
