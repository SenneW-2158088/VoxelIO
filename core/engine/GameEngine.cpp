//
// Created by Senne Wertelaers on 30/03/2024.
//

#include "GameEngine.h"

#include <iostream>
#include <manager/AssetManager.h>

GameEngine::GameEngine() {
    EngineConfig config = {640, 480, "Hello World"};
    this->config = config;
}

GameEngine::GameEngine(const EngineConfig &config) {
    this->config = config;
}

GameEngine::~GameEngine() {
    AssetManager::clearAssets();

    glfwTerminate();
}

void GameEngine::start() {
    this->init();
    this->gameLoop();
}

void GameEngine::init() {
    this->window = initGLFW();
    initGlad();

    // Initialize assets after opengl context is created
    AssetManager::initializeAssets();

    glfwSetWindowSizeCallback(this->window, onResize);
}

void GameEngine::gameLoop() {
    while (!glfwWindowShouldClose(this->window)) {
        this->render();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void GameEngine::render() {
    // TODO: Implement rendering pipeline
    // Update the model matrix from camera
}

GLFWwindow *initGLFW() {
    GLFWwindow* window;

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

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetErrorCallback(error_callback);

    return window;
}

void initGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void onResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}