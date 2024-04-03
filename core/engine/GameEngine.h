//
// Created by Senne Wertelaers on 30/03/2024.
//

#ifndef VOXELIO_GAMEENGINE_H
#define VOXELIO_GAMEENGINE_H

#include <vector>
#include <model/Entity.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/Uniform.h>
#include <manager/InputManager.h>
#include <manager/WindowManager.h>

struct EngineConfig {
    int width;
    int height;
    const char *title;
};

class GameEngine {
private:
    WindowManager* windowManager;
    EngineConfig config;
    InputManager *inputManager;
    Uniform::GameUniform *uniform;
    std::vector<Entity*> entities{};
private:
    void gameLoop();

    void render();

public:
    void addInputListener(InputListener *listener);

    void addEntity(Entity *entity);

public:
    GameEngine(const EngineConfig &config);

    ~GameEngine();

    void start();
};


#endif //VOXELIO_GAMEENGINE_H
