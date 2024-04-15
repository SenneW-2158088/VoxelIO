#pragma once

#include "gameplay/Chunk.h"
#include <cstddef>
#include <gameplay/Noise.h>
#include <generator/Generator.hpp>


class BasicChunkGenerator : public Generator<Chunk, glm::vec2> {
private:
  const size_t size = 16;
  noise::Noise *noise;
public:
  BasicChunkGenerator(noise::Noise *noise) : noise{noise}{}
  ~BasicChunkGenerator() = default;
  Chunk * generate(glm::vec2 pos) const override;
};
