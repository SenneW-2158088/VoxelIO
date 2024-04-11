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

  auto c1 = Collision::Collisioner(
    nullptr,
    new Collision::AABoundingBox({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 2.5f,2.f})
  );

  auto t1 = Collision::Collisioner( nullptr, new Collision::AABoundingBox({0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f,1.f}) );
  auto t2 = Collision::Collisioner( nullptr, new Collision::AABoundingBox({0.f, 2.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 3.f,1.f}) );
  auto t3 = Collision::Collisioner( nullptr, new Collision::AABoundingBox({0.f, 0.f, 2.f}, {0.f, 0.f, 0.f}, {1.f, 1.f,1.f}) );

  auto t4 = Collision::Collisioner( nullptr, new Collision::AABoundingBox({0.f, 0.f, 1.f}, {0.f, 0.f, 0.f}, {2.f, 2.f,2.f}) );

  auto tree = Collision::CollisionerOctree();
  tree.insert(&t1);
  tree.insert(&t2);
  tree.insert(&t3);

  auto found = tree.query(c1);

  for (const auto& i : found){
    std::cout << "c1 collided with: " << glm::to_string(i->getBoundingBox()->getPosition()) << std::endl;
  }

  tree.print_tree();

  // Game game = Game{};
  // game.start();

  return 0;
}
