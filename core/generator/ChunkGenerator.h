#pragma once

#include <gameplay/Noise.h>

template<typename T>
class ChunkGeneratorBase { 
public:
  ChunkGeneratorBase() = default;
  virtual T generate(Noise::BasicNoise * noise) const = 0;
};

/*
  Very basic terrain generator for a basic chunk
*/
struct {
  
} typedef BasicChunkData;

class BasicChunkGenerator : ChunkGeneratorBase<BasicChunkData> {
  BasicChunkData generate(Noise::BasicNoise *noise) const override;
};
