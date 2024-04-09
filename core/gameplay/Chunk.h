#pragma once

#include "gameplay/Collision.h"
#include "graphics/Mesh.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <unordered_map>
#include <vector>

// Very basic shitty chunk with individual voxels
class Chunk {
private:
public:
  Chunk() = default;
  virtual void draw() const = 0;

  virtual std::vector<Entity*> getEntities() const = 0;
};

class BasicChunk : public Chunk {
private:
  std::vector<Entity *> voxels;
public:
  BasicChunk();
  void draw() const override;
  std::vector<Entity *> getEntities() const override { return voxels; };
};

class InstancedChunk : public Chunk {
  InstancedVoxel* voxels;
public:
  InstancedChunk();
  void draw() const override;
  std::vector<Entity *> getEntities() const override { return std::vector<Entity *>{voxels}; };
};
