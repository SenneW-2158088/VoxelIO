//
// Created by Senne Wertelaers on 30/03/2024.
//

#ifndef VOXELIO_GAMEENGINE_H
#define VOXELIO_GAMEENGINE_H

#include "gameplay/Chunk.h"
#include "gameplay/Collision.h"
#include "manager/CameraHandler.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <graphics/Uniform.h>
#include <manager/InputManager.h>
#include <manager/WindowManager.h>
#include <model/Camera.h>
#include <model/Entity.h>
#include <gameplay/Terrain.hpp>
#include <optional>
#include <vector>

struct EngineConfig {
  int width;
  int height;
  const char *title;
};

class GameEngine : InputListener {
private:
  WindowManager *windowManager;
  EngineConfig config;
  CameraHandler *cameraHandler;
  InputManager *inputManager;

  std::optional<Camera *> camera;

  // Graphics data objects
  Uniform::GameUniform *gameUniform;
  Uniform::LightingUniform *lightingUniform;

  // Core objects
  std::vector<Entity *> entities{};
  std::vector<Collision::Collisionable *> collisioners{};
  std::vector<Terrain *> terrains{};

private:
  void gameLoop();

  void update(float dt);

  void handleCollisions();

  void render();

public:
  void addInputListener(InputListener *listener);

  void addEntity(Entity *entity);

  void addTerrain(Terrain *terrain);

  void setCamera(Camera *camera);

  void onInput(InputKeymap key) override;

public:
  GameEngine(const EngineConfig &config);

  ~GameEngine();

  void start();
};

#endif // VOXELIO_GAMEENGINE_H
