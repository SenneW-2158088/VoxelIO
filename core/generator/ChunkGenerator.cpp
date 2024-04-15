#include "ChunkGenerator.h"
#include "gameplay/Chunk.h"

Chunk* BasicChunkGenerator::generate(glm::vec2 pos) const { 
  return new InstancedChunk(*noise, glm::vec3{pos.x * 16.f, 0.f, pos.y * 16.f});
}
