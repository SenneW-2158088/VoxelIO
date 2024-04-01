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

GLFWwindow *initGLFW(int width, int height, const char *title);

void initGlad();

void onResize(GLFWwindow *window, int width, int height);

void error_callback(int error, const char* description);

struct EngineConfig {
    int width;
    int height;
    const char *title;
};

class GameEngine {
private:
    GLFWwindow *window;
    EngineConfig config;
    InputManager* inputManager;
    std::vector<Entity> entities{};
private:
    void init();

    void gameLoop();

    void render();

public:
    void addInputListener(InputListener *listener);
public:
    GameEngine();

    explicit GameEngine(const EngineConfig &config);

    ~GameEngine();

    void start();
};


#endif //VOXELIO_GAMEENGINE_H
