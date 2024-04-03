//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"
#include "model/Triangle.h"
#include <model/Player.h>
#include <graphics/Uniform.h>

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
    Triangle *triangle = new Triangle();
    Voxel *voxel = new Voxel();
    engine->addEntity(triangle);
    engine->addEntity(voxel);
    engine->start();
}
