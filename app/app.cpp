//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "manager/ChunkManager.h"
#include <algorithm>
#include <game/Game.h>
#include <gameplay/Noise.h>
#include <gameplay/db_perlin.h>
#include <iostream>
#include <memory>

int main() {

  LRUChunkCache<int, Test> cache{2};

  cache.put(1, std::make_shared<Test>(1));
  cache.put(2, std::make_shared<Test>(2));
  cache.put(3, std::make_shared<Test>(3));
  cache.put(4, std::make_shared<Test>(4));

  auto c2 = cache.get(2);
  if(auto c2ptr = c2.lock()){
    std::cout << "lost c2" << std::endl;
  }

  // Game game = Game{};
  // game.start();

  return 0;
}
