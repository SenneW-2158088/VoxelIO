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
    Triangle *triangle = new Triangle();
    Voxel *voxel = new Voxel();
    PerspectiveCamera* camera = PerspectiveCameraBuilder()
        .setPosition(glm::vec3{0.f, 0.f, 3.f})
        ->setDirection(glm::vec3{0.f, 0.f, -1.f}) // looking forward in z direction
        ->setField(45.f)
        ->setAspect(16.f / 9.f)
        ->build();

    engine->setCamera(camera);
    engine->addEntity(triangle);
    engine->addEntity(voxel);
    engine->start();
}
