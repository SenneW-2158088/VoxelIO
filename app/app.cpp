//
// Created by Senne Wertelaers on 28/03/2024.
//
#include "gameplay/Collision.h"
#include "glm/gtx/string_cast.hpp"
#include "manager/ChunkManager.h"
#include <algorithm>
#include <game/Game.h>
#include <gameplay/Noise.h>
#include <gameplay/db_perlin.h>
#include <iostream>
#include <memory>

int main() {

  auto noise = noise::Perlin(256);

  for (float x = -16; x < 0; x += 0.2f) {

    for (float z = -16; z < 0; z += 0.2f) {
      std::cout << "("<< x << ", " << z << ") ";
      std::cout << noise.noise(x , z) << std::endl; 
    }
  }

  std::cout << ((int)std::floor(-4.2) & 0xFF) << std::endl;

  Game game = Game{};
  game.start();

  return 0;
}
