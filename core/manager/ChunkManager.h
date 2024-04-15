#pragma once

#include <memory>

#include "gameplay/Chunk.h"
#include "generator/Generator.hpp"
#include "manager/Cache.h"

class ChunkManager {
private:
  const size_t cacheCapacity = 1 << 13;

  LRUChunkCache<glm::vec2, Chunk> LRU;
  Generator<Chunk, glm::vec2> *generator;

public:
  ChunkManager(Generator<Chunk, glm::vec2> &);
  ~ChunkManager() = default;
  std::weak_ptr<Chunk> load(glm::vec2 position);
};
