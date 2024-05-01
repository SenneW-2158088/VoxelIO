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

void VoxelTerrain::collide(Collision::Collisionable &other){
  for(const auto &col : other.getCollisioners()){
    auto new_pos = glm::vec3{
        std::floor(col->getBoundingBox()->getPosition().x / 16),
        0.f,
        std::floor(col->getBoundingBox()->getPosition().z / 16),
    };
    std::cout << "Trying to collide with chunk: " << glm::to_string(new_pos) << std::endl;
    Chunk* toCollide = chunkManager->load(new_pos).lock().get();
    for(auto e : toCollide->getEntities()){
      const auto c = dynamic_cast<Collision::Collisionable *>(e);
      if(c){
        std::cout << "Let player collide with" << e->getName() << std::endl;
        c->collide(other);
      }
    }
  }
}
