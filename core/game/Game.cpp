//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"
#include "gameplay/Terrain.hpp"
#include "model/Triangle.h"
#include <model/VoxelTerrain.h>
#include <model/Voxel.h>
#include <model/Camera.h>
#include <model/Player.h>

#include <graphics/Uniform.h>
#include <glm/glm.hpp>

Game::Game() {
    EngineConfig config = EngineConfig{
            1920 / 2,
            1080 / 2,
            "Voxelio",
    };

    engine = new GameEngine(config);
}

void Game::start() {
    // Add player
    Player* player = new PlayerImplementation();
    player->setPosition(glm::vec3{0.f, 0.f, -3.f});

    engine->addInputListener(player);
    engine->setCamera(player->getCamera());
    engine->addEntity(player);

    // Add terain
    Terrain* voxelTerrain = new VoxelTerrain();
    engine->addTerrain(voxelTerrain);

    // Start engine
    engine->start();
}
