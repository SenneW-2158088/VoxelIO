#pragma once

#include "gameplay/Noise.h"
#include "model/Entity.h"
#include "model/Voxel.h"
#include <vector>

// Very basic shitty chunk with individual voxels
class Chunk {
protected:
  const size_t size = 16; // Chunk size ^2
  const size_t height = 256; // max height of the chunk
  const size_t base = 2;
public:
  Chunk() = default;
  virtual ~Chunk() = default;
  virtual void draw() const = 0;
  virtual std::vector<Entity*> getEntities() const = 0;
};

class BasicChunk : public Chunk {
private:
  std::vector<Entity *> voxels;
public:
  BasicChunk(const noise::Noise &noise);
  void draw() const override;
  std::vector<Entity *> getEntities() const override { return voxels; };
};

class InstancedChunk : public Chunk {
  InstancedVoxel* voxels;
public:
  InstancedChunk(const noise::Noise &noise, glm::vec3 position);
  void draw() const override;
  std::vector<Entity *> getEntities() const override { return std::vector<Entity *>{voxels}; };
};
