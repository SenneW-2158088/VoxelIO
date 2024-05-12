#include "VoxelTerrain.h"
#include "gameplay/Chunk.h"
#include "gameplay/Collision.h"
#include "gameplay/Noise.h"
#include "generator/ChunkGenerator.h"
#include "generator/Generator.hpp"
#include "glm/gtx/string_cast.hpp"
#include "manager/ChunkManager.h"
#include <iostream>
#include <memory>
#include <ostream>

VoxelTerrain::VoxelTerrain() {
  noise::Noise *noise = new noise::Perlin(16);
  Generator<Chunk, glm::vec2> *generator = new BasicChunkGenerator(noise);
  chunkManager = new ChunkManager(*generator);
}

VoxelTerrain::~VoxelTerrain() {
  delete noise;
  delete generator;
}

void VoxelTerrain::draw() const {
  const auto offset = floor((2 + 3 * distance) / 2);

  for (int x = base_position.x - offset; x < base_position.x + offset; x++) {
    for (int z = base_position.z - offset; z < base_position.z + offset; z++) {
      auto chunk = chunkManager->load(glm::vec2{x, z}).lock();
      if (chunk.get()) {
        chunk.get()->draw();
      }
    }
  }
}

void VoxelTerrain::update(const float dt) {
  // TODO implement update code
}

void VoxelTerrain::collide(Collision::Collisionable &other) {
  const auto offset = floor((2 + 3 * distance) / 2);

  for (int x = base_position.x - offset; x < base_position.x + offset; x++) {
    for (int z = base_position.z - offset; z < base_position.z + offset; z++) {
      auto chunk = chunkManager->load(glm::vec2{x, z}).lock();
      if (chunk.get()) {
        for (auto e : chunk->getEntities()) {
          const auto c = dynamic_cast<Collision::Collisionable *>(e);
          if (c) {
            // std::cout << "Let player collide with" << e->getName() << std::endl;
            c->collide(other);
          }
        }
      }
    }
  }
}

glm::vec3 VoxelTerrain::getSpawnPos(glm::vec3 position){
  auto new_pos = glm::vec3{
      std::floor(position.x / 16),
      0.f,
      std::floor(position.z / 16),
  };
  auto c = chunkManager->load(base_position).lock();
  return c->getSpawnPos(position);
}
