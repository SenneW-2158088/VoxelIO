//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "InputManager.h"

InputManager::InputManager(GLFWwindow *window) : window{window} {}

void InputManager::handleInput() {
    handleMouse();

    for (InputListener* listener : listeners) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            listener->onKeyPressed(GLFW_KEY_W);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            listener->onKeyPressed(GLFW_KEY_A);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            listener->onKeyPressed(GLFW_KEY_S);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            listener->onKeyPressed(GLFW_KEY_D);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            listener->onKeyPressed(GLFW_KEY_SPACE);
        }


//        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
//            listener->onKeyReleased(GLFW_KEY_W);
//        }
//        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
//            listener->onKeyReleased(GLFW_KEY_A);
//        }
//        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
//            listener->onKeyReleased(GLFW_KEY_S);
//        }
//        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
//            listener->onKeyReleased(GLFW_KEY_D);
//        }
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
//            listener->onKeyPressed(GLFW_KEY_SPACE);
//        }
    }
}

void InputManager::handleMouse() {
    glfwGetCursorPos(window, &cursor_x, &cursor_y);
    for (InputListener* listener : listeners) {
        listener->onMouseMove(cursor_x, cursor_y);
    }
}

void InputManager::addInputListener(InputListener *listener) {
    listeners.push_back(listener);
}
