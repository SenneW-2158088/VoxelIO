//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"
#include "model/Triangle.h"
#include <model/Player.h>
#include <graphics/Uniform.h>

#include <model/Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <model/Voxel.h>

Game::Game() {
    EngineConfig config = EngineConfig{
            1920 / 2,
            1080 / 2,
            "Voxelio",
    };

    engine = new GameEngine(config);
}

void Game::start() {
    Player* player = new PlayerImplementation();
    player->setPosition(glm::vec3{0.f, 0.f, -3.f});

    engine->addInputListener(player);
    engine->setCamera(player->getCamera());
    engine->addEntity(player);
    engine->start();
}
