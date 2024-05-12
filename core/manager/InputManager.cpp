//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "InputManager.h"
#include "GLFW/glfw3.h"

InputManager::InputManager(GLFWwindow *window) : window{window} {}

void InputManager::handleInput() {
  handleMouse();

  const auto up = glfwGetKey(window, GLFW_KEY_W);
  const auto left = glfwGetKey(window, GLFW_KEY_A);
  const auto down = glfwGetKey(window, GLFW_KEY_S);
  const auto right = glfwGetKey(window, GLFW_KEY_D);
  const auto space = glfwGetKey(window, GLFW_KEY_SPACE);
  const auto shift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
  const auto interact = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

  for (const auto listener : listeners) {
    listener->onInput(
        InputKeymap{up, down, left, right, space, shift, interact});
  }
}

void InputManager::handleMouse() {
  glfwGetCursorPos(window, &cursor_x, &cursor_y);
  for (InputListener *listener : listeners) {
    listener->onMouseMove(cursor_x, cursor_y);
  }
}

void InputManager::addInputListener(InputListener *listener) {
  listeners.push_back(listener);
}
