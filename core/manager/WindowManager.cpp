//
// Created by Senne Wertelaers on 03/04/2024.
//

#include "WindowManager.h"
#include "GLFW/glfw3.h"
#include <iostream>

WindowService::WindowService(int width, int height, const char *title) {
    initGLFW(width, height, title);
    initGlad();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    // TODO
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // TODO
    glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, onResize);
}

float WindowService::getDelta() {
    const float newTime = glfwGetTime();
    const float delta = newTime - time;
    time = newTime;
    return delta;
}

void WindowService::update() const {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowService::clear() const {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowService::resize(int width, int height) {
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);

    if (callback) {
        callback(width, height);
    }

    std::cout << "resize to " << width << "x" << height << std::endl;
}

bool WindowService::shouldClose() {
    return glfwWindowShouldClose(window);
}

void WindowService::setResizeCallback(void (*callback)(int, int)) {
    this->callback = callback;
}

void WindowService::initGLFW(int width, int height, const char *title) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#ifdef __APPLE__
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

    glfwMakeContextCurrent(window);
}

void WindowService::initGlad() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void onResize(GLFWwindow *, int width, int height) {
    WindowLocator::get()->resize(width, height);
}

void error_callback(int, const char *description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}


WindowManager* WindowLocator::windowManager = nullptr;

void WindowLocator::provide(WindowManager *windowManager) {
    WindowManager *manager = windowManager;

    if (!manager) {
        manager = new NullWindowService();
    }

    WindowLocator::windowManager = manager;
}

WindowManager *WindowLocator::get() {
    return windowManager;
}
