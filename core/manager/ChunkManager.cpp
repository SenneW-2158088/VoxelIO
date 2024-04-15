#include "ChunkManager.h"
#include "gameplay/Chunk.h"
#include "generator/ChunkGenerator.h"
#include <memory>

ChunkManager::ChunkManager(Generator<Chunk, glm::vec2> &generator)
    : LRU{cacheCapacity}, generator{&generator} {}

std::weak_ptr<Chunk> ChunkManager::load(glm::vec2 position) {
  // Check if chunk is cached
  auto cached = LRU.get(position);
  if (cached.lock()) {
    return cached;
  }

  // load from generator
  Chunk* chunk = generator->generate(position);
  LRU.put(position, std::shared_ptr<Chunk>(chunk));

  return std::weak_ptr<Chunk>(LRU.get(position));
}
