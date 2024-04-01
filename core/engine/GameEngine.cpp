//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"

#include <iostream>
#include <manager/AssetManager.h>

GameEngine::GameEngine() {
    EngineConfig engineConfig = {640, 480, "Hello World"};
    config = engineConfig;
    init();
}

GameEngine::GameEngine(const EngineConfig &engineConfig) {
    config = engineConfig;
    init();
}

GameEngine::~GameEngine() {
    AssetManager::clearAssets();

    glfwTerminate();
}

void GameEngine::start() {
//    this->init();
    this->gameLoop();
}

void GameEngine::init() {
    this->window = initGLFW(
            this->config.width,
            this->config.height,
            this->config.title
    );
    initGlad();

    // Initialize assets after opengl context is created
    AssetManager::initializeAssets();

    // Set input manager
    this->inputManager = new InputManager(this->window);

    // Set the resize callback
    glfwSetWindowSizeCallback(this->window, onResize);
}

void GameEngine::gameLoop() {
    while (!glfwWindowShouldClose(this->window)) {
        inputManager->handleInput();

        render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void GameEngine::render() {
    // TODO: Implement rendering pipeline
    // Update the model matrix from camera
}

void GameEngine::addInputListener(InputListener *listener) {
    inputManager->addInputListener(listener);
}

GLFWwindow *initGLFW(int width, int height, const char *title) {
    GLFWwindow *window;

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

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