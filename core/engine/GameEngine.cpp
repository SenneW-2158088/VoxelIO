//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <manager/AssetManager.h>

GameEngine::GameEngine() {
    EngineConfig engineConfig = {640, 480, "Hello pls set a title"};
    config = engineConfig;
    init();
}

GameEngine::GameEngine(const EngineConfig &engineConfig) {
    config = engineConfig;
    init();
}

GameEngine::~GameEngine() {
    std::cout << "Destroying GameEngine" << std::endl;
    AssetManager::clearAssets();
    glfwTerminate();
}

void GameEngine::start() {
    this->gameLoop();
}

void GameEngine::init() {

    this->window = initGLFW(
            this->config.width,
            this->config.height,
            this->config.title
    );

    initGlad();

    glViewport(0, 0, config.width, config.height);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize assets after opengl context is created
    AssetManager::initializeAssets();

    // Set the resize callback
    glfwSetWindowSizeCallback(this->window, onResize);
}

void GameEngine::gameLoop() {
    while (!glfwWindowShouldClose(this->window)) {
//        inputManager->handleInput();
        render();
    }
}

void GameEngine::render() {
    // TODO: Implement rendering pipeline
    // Update the model matrix from camera
    // Render all entities

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(const auto&entity : entities) {
        entity->draw();
    }

    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void GameEngine::addInputListener(InputListener *listener) {
    inputManager->addInputListener(listener);
}

void GameEngine::addEntity(Entity* entity) {
    entities.push_back(entity);
}

GLFWwindow *initGLFW(int width, int height, const char *title) {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();

        std::cout << "Failed to create window" << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    unsigned int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    std::cout << "opengl shader version: " << major << "." << minor << std::endl;

// Make the window's context current
    glfwMakeContextCurrent(window);

// Disable cursor
    glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetErrorCallback(error_callback);

    return window;
}

void initGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void onResize(GLFWwindow *, int width, int height) {
    glViewport(0, 0, width, height);
}

void error_callback(int, const char *description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}