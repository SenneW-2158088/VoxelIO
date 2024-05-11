//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"
#include "gameplay/Chunk.h"
#include "gameplay/Collision.h"
#include "glad/glad.h"
#include "glm/fwd.hpp"
#include "graphics/Lighting.h"
#include "graphics/Uniform.h"
#include "manager/CameraHandler.h"
#include "manager/InputManager.h"
#include "model/Entity.h"
#include "model/Player.h"
#include "model/PointLightBuffer.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <manager/AssetManager.h>
#include <memory>
#include <optional>
#include <vector>

GameEngine::GameEngine(const EngineConfig &engineConfig) {
  config = engineConfig;

  WindowLocator::provide(
      new WindowService(config.width, config.height, config.title));
  windowManager = WindowLocator::get();

  gameUniform = new Uniform::GameUniform(
      glm::perspective(glm::radians(45.0f),
                       (float)config.width / (float)config.height, 0.1f,
                       100.0f),
      glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f)),
      glm::vec4(0.0f, 0.0f, 3.0f, 1.0f));

  auto dirLight = lighting::DirectionalLight();
  lightingUniform = new Uniform::LightingUniform(dirLight);

  // Todo provide with player camera
  UniformLocator::provideGame(gameUniform);
  UniformLocator::provideLighting(lightingUniform);

  pointLightBuffer = new PointLightBuffer();
  pointLightBuffer->addPointLight(
    new lighting::PointLight(
      glm::vec3{0.9f, 0.2f, 0.0f},
      glm::vec3{0.3f, 0.2f, 0.8f},
      glm::vec3{0.3f, 0.2f, 0.8f},
      glm::vec3{0.f, 4.f, 30.f},
      1.f,
      1.f,
      0.032f
    )
  );
  pointLightBuffer->addPointLight(
    new lighting::PointLight(
      glm::vec3{1.0f, 0.0f, 0.8f},
      glm::vec3{1.0f, 0.2f, 0.8f},
      glm::vec3{1.0f, 0.2f, 0.8f},
      glm::vec3{0.f, 2.f, 0.f},
      1.f,
      0.09f,
      0.032f
    )
  );

  pointLightBuffer->buffer();

  // pointLightBuffer->bind(0);


  // glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  // GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
  // memcpy(p, &v, sizeof(v));
  // glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  windowManager->setResizeCallback([](int width, int height) {
    // Get uniform
    auto uniform = UniformLocator::getGame();
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

    handleCollisions();
  }
}

void GameEngine::update(float dt) {
  std::vector<int> toRemove{};

  for (const auto &entity : entities) {
    if(entity->isAlive()){
      entity->update(dt);
    }
    else {
      std::vector<Entity*>::iterator position = std::find(entities.begin(), entities.end(), entity);
      if (position != entities.end()){
        entities.erase(position);
      }

      std::vector<Collision::Collisionable*>::iterator pos = std::find(collisioners.begin(), collisioners.end(), (Collision::Collisionable *) entity);
      if (position != entities.end()){
        collisioners.erase(pos);
      }

    }

    for (const auto &terrain : terrains) {
      if (camera.has_value()) {
        auto new_pos = glm::vec3{
            std::floor(camera.value()->getPosition().x / 16),
            0.f,
            std::floor(camera.value()->getPosition().z / 16),
        };
        terrain->setBasePosition(new_pos);
      }
    }
  }

  for (const auto &terrain : terrains) {
    terrain->update(dt);
  }
}

void GameEngine::handleCollisions() {
  for (const auto &collisioner : collisioners) {
    for (const auto &other : collisioners) {
      if (collisioner != other) {
        // collide with other collisioners
        collisioner->collide(*other);
      }
    }

    // collide with terrain
    for (const auto &terrain : terrains) {
      terrain->collide(*collisioner);
    }
  }
}

void GameEngine::render() {
  windowManager->clear();

  // update Uniform buffer
  if (camera.has_value()) {
    auto uniform = UniformLocator::getGame();
    auto c = camera.value();
    uniform->setProjection(c->getProjection());
    uniform->setView(c->getView());
    uniform->setViewPos(glm::vec4(c->getPosition(), 0.f));
    cameraHandler->updateCamera(c);
  }

  for (const auto &entity : entities) {
    entity->draw();
  }

  for (const auto &terrain : terrains) {
    terrain->draw();
  }

  windowManager->update();
}

void GameEngine::setCamera(Camera *camera) { this->camera.emplace(camera); }

void GameEngine::addInputListener(InputListener *listener) {
  inputManager->addInputListener(listener);
}

void GameEngine::addEntity(Entity *entity) {
  entities.push_back(entity);
  if (const auto c{dynamic_cast<Collision::Collisionable *>(entity)}) {
    collisioners.push_back(c);
    std::cout << "Adding " << entity->getName() << " to collisioners"
              << std::endl;
  }
}

void GameEngine::addTerrain(Terrain *terrain) { terrains.push_back(terrain); }

void GameEngine::onInput(InputKeymap map) {}
