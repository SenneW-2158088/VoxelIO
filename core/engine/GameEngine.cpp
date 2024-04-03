//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <manager/AssetManager.h>

GameEngine::GameEngine(const EngineConfig &engineConfig) {
    config = engineConfig;

    WindowLocator::provide(new WindowService(config.width, config.height, config.title));
    windowManager = WindowLocator::get();

    uniform = new Uniform::GameUniform(
            glm::perspective(glm::radians(45.0f), (float) config.width / (float) config.height, 0.1f, 100.0f),
            glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
            glm::vec4(0.0f, 0.0f, 3.0f, 1.0f)
    );

    windowManager->setResizeCallback([](int width, int height) {

    });

    // Initialize assets after opengl context is created
    AssetManager::initializeAssets();

    // Set the resize callback
}

GameEngine::~GameEngine() {
    std::cout << "Destroying GameEngine" << std::endl;
    AssetManager::clearAssets();
    glfwTerminate();
}

void GameEngine::start() {
    this->gameLoop();
}

void GameEngine::gameLoop() {
    while (!windowManager->shouldClose()){
//        inputManager->handleInput();
        render();

    }
}

void GameEngine::render() {
    windowManager->clear();

    for(const auto&entity : entities) {
        entity->draw();
    }

    windowManager->update();
}

void GameEngine::addInputListener(InputListener *listener) {
    inputManager->addInputListener(listener);
}

void GameEngine::addEntity(Entity* entity) {
    entities.push_back(entity);
}