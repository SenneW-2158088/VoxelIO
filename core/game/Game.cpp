//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Game.h"
#include "gameplay/Terrain.hpp"
#include "model/Box.h"
#include "model/Skybox.h"
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

    // Add cubemap
    Skybox* skybox = new Skybox(); 
    engine->addEntity(skybox);

    // Add terain
    Terrain* voxelTerrain = new VoxelTerrain();
    engine->addTerrain(voxelTerrain);

    // Basic voxel for testing
    // Voxel* voxel = new Voxel(glm::vec3 {0.f, 0.f, 0.f});
    // Voxel* voxel2 = new Voxel(glm::vec3 {0.f, 0.f, 1.f});
    // Voxel* voxel3 = new Voxel(glm::vec3 {1.f, 0.f, 0.f});
    // engine->addEntity(voxel);
    // engine->addEntity(voxel2);
    // engine->addEntity(voxel3);

    Voxel* voxel4 = new Voxel(glm::vec3 {3.f, 0.f, 0.f});
    Voxel* voxel5 = new Voxel(glm::vec3 {3.f, 0.f, 1.f});
    // engine->addEntity(voxel4);
    // engine->addEntity(voxel5);

    // Box
    // Box *box = new Box(glm::vec3 {0.f, 0.f, 2.f});
    // engine->addEntity(box);

    // Start engine
    engine->start();
}
