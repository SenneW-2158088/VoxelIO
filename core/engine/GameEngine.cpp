//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"
#include "gameplay/Collision.h"
#include "graphics/Uniform.h"
#include "manager/CameraHandler.h"
#include "manager/InputManager.h"
#include "model/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <manager/AssetManager.h>
#include <memory>
#include <optional>

GameEngine::GameEngine(const EngineConfig &engineConfig) {
  config = engineConfig;

  WindowLocator::provide(
      new WindowService(config.width, config.height, config.title));
  windowManager = WindowLocator::get();

  uniform = new Uniform::GameUniform(
      glm::perspective(glm::radians(45.0f),
                       (float)config.width / (float)config.height, 0.1f,
                       100.0f),
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f)),
      glm::vec4(0.0f, 0.0f, 3.0f, 1.0f));

  // Todo provide with player camera
  UniformLocator::provide(uniform);

  windowManager->setResizeCallback([](int width, int height) {
    // Get uniform
    auto uniform = UniformLocator::get();
    // uniform->setProjection(glm::perspective(45.f, (float) width / (float)
    // height, .1f, 100.f));
  });

  // Initialize assets after opengl context is created
  AssetManager::initializeAssets();

  // Camera input handler
  cameraHandler = new CameraHandler(0.1f);

  const auto window = windowManager->getWindow();
  inputManager = new InputManager(window);
  addInputListener(this);
  addInputListener(cameraHandler);
}

GameEngine::~GameEngine() {
  std::cout << "Destroying GameEngine" << std::endl;
  AssetManager::clearAssets();
  glfwTerminate();
}

void GameEngine::start() { this->gameLoop(); }

void GameEngine::gameLoop() {
  while (!windowManager->shouldClose()) {
    inputManager->handleInput();

    update(windowManager->getDelta());

    render();
  }
}

void GameEngine::update(float dt){
  for (const auto &entity : entities){
    entity->update(dt);
  }
}

void GameEngine::handleCollisions(){
  for(const auto& collisioner : collisioners){
    for(const auto& other : collisioners) {
      if(collisioner != other) {
        collisioner->collide(*other);
      }
    }
  }
}

void GameEngine::render() {
  windowManager->clear();

  // update Uniform buffer
  if (camera.has_value()) {
    auto uniform = UniformLocator::get();
    auto c = camera.value();
    uniform->setProjection(c->getProjection());
    uniform->setView(c->getView());
    uniform->setViewPos(glm::vec4(c->getPosition(), 0.f));
    cameraHandler->updateCamera(c);
  }


  for (const auto &entity : entities) {
    entity->draw();
  }

  windowManager->update();
}

void GameEngine::setCamera(Camera *camera) { this->camera.emplace(camera); }

void GameEngine::addInputListener(InputListener *listener) {
  inputManager->addInputListener(listener);
}

void GameEngine::addEntity(Entity *entity) { 
  entities.push_back(entity);
  if(const auto c{dynamic_cast<Collision::Collisionable*>(entity)}){
    collisioners.push_back(c);
    std::cout << "Adding " << entity->getName() << " to collisioners" << std::endl;
  }
}

void GameEngine::onInput(InputKeymap map) {

}
