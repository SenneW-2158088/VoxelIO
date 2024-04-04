//
// Created by Senne Wertelaers on 30/03/2024.
//

#ifndef VOXELIO_GAMEENGINE_H
#define VOXELIO_GAMEENGINE_H

#include "manager/CameraHandler.h"
#include <vector>
#include <model/Entity.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/Uniform.h>
#include <manager/InputManager.h>
#include <manager/WindowManager.h>
#include <model/Camera.h>
#include <optional>

struct EngineConfig {
    int width;
    int height;
    const char *title;
};

class GameEngine : InputListener {
private:
    WindowManager* windowManager;
    EngineConfig config;
    CameraHandler *cameraHandler;
    InputManager *inputManager;

    std::optional<Camera*> camera;
    Uniform::GameUniform *uniform;
    std::vector<Entity*> entities{};
private:
    void gameLoop();

    void render();

public:
    void addInputListener(InputListener *listener);

    void addEntity(Entity *entity);

    void setCamera(Camera *camera);

    void onKeyPressed(int key) override;

public:
    GameEngine(const EngineConfig &config);

    ~GameEngine();

    void start();
};


#endif //VOXELIO_GAMEENGINE_H
