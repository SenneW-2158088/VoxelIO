//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"

Game::Game() {
    EngineConfig config = EngineConfig {
       1920,
       1080,
         "Voxelio",
    };

    engine = new GameEngine(config);
}

void Game::start() {
    engine->start();
}
