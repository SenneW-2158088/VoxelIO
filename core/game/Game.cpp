//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"
#include <model/Player.h>

Game::Game() {
    EngineConfig config = EngineConfig {
       1920,
       1080,
         "Voxelio",
    };

    engine = new GameEngine(config);
}

void Game::start() {
    Player* player = new PlayerImplementation();
    engine->addInputListener(player);
    engine->start();
}
