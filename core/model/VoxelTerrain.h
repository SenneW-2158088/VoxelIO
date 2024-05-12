#pragma once

#include "gameplay/Noise.h"
#include "generator/ChunkGenerator.h"
#include "manager/ChunkManager.h"
#include <gameplay/Terrain.hpp>

// Voxel terrain 
class VoxelTerrain : public Terrain {
  const size_t distance = 9;

  noise::Perlin* noise;
  BasicChunkGenerator* generator;

  ChunkManager* chunkManager;
public:
  VoxelTerrain();
  ~VoxelTerrain();
  void draw() const override;
  void update(const float dt) override;
  void collide(Collision::Collisionable &other) override;
  glm::vec3 getSpawnPos(glm::vec3 position);
};
