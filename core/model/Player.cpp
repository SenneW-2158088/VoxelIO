//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Player.h"
#include "GLFW/glfw3.h"
#include "gameplay/State.h"
#include "manager/InputManager.h"
#include "model/Camera.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <optional>

PlayerStates::PlayerState::PlayerState(Player *player)
    : BaseState<Player, PlayerState>(player) {}


// Idle state
std::optional<PlayerStates::PlayerState *>
PlayerStates::IdleState::handleInput(InputKeymap map) {
  const auto notWalking = map.down == GLFW_RELEASE && map.up == GLFW_RELEASE && map.left == GLFW_RELEASE && map.right == GLFW_RELEASE;
  std::cout << "not walking: " << notWalking << std::endl;

  if (notWalking) {
    return std::nullopt;
  }

  return new PlayerStates::WalkingState(entity);
}

// Walking state
std::optional<PlayerStates::PlayerState *>
PlayerStates::WalkingState::handleInput(InputKeymap map) {
  const auto walking = map.down == GLFW_PRESS || map.up == GLFW_PRESS || map.left == GLFW_PRESS || map.right == GLFW_PRESS;
  std::cout << "walking: " << walking << std::endl;

  if (map.up == GLFW_PRESS) entity->forward();
  if (map.left == GLFW_PRESS) entity->left();
  if (map.down == GLFW_PRESS) entity->backward();
  if (map.right == GLFW_PRESS) entity->right();

  if (walking) {
    return std::nullopt;
  }

  return new IdleState(entity);
}


// Jumping state
std::optional<PlayerStates::PlayerState *>
PlayerStates::JumpingState::handleInput(InputKeymap map) {}

// Running state
std::optional<PlayerStates::PlayerState *>
PlayerStates::RunningState::handleInput(InputKeymap map) {}

PlayerImplementation::PlayerImplementation() : direction{} {
  PerspectiveCamera *camera =
      PerspectiveCameraBuilder()
          .setPosition(glm::vec3{0.f, 0.f, 3.f})
          ->setDirection(
              glm::vec3{0.f, 0.f, -1.f}) // looking forward in z direction
          ->setField(45.f)
          ->setAspect(16.f / 9.f)
          ->build();

  this->camera = camera;

  state = new PlayerStates::IdleState(this);
}

void PlayerImplementation::onInput(InputKeymap map) {
  transition(state->handleInput(map));
}

void PlayerImplementation::transition(std::optional<PlayerStates::PlayerState *> state) {
  if (state.has_value()) {
    std::cout << "Changing to: " << state.value()->toString() << std::endl;
    delete this->state;
    this->state = state.value();
  }
}

void PlayerImplementation::update(float dt) {
  this->position += direction * speed;
  camera->setPosition(position + glm::vec3{0.f, height, 0.f});

  direction = glm::vec3{0};

  std::cout << glm::to_string(position) << std::endl;
}

// Todo normalize with camera direction
void PlayerImplementation::forward() { direction += glm::vec3{0.f, 0.f, -1.f}; }
void PlayerImplementation::backward() { direction += glm::vec3{0.f, 0.f, 1.f}; }
void PlayerImplementation::left() { direction += glm::vec3{-1.f, 0.f, 0.f}; }
void PlayerImplementation::right() { direction += glm::vec3{1.f, 0.f, 0.f}; }

void PlayerImplementation::draw() {}
