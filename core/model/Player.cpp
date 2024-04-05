//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Player.h"
#include "GLFW/glfw3.h"
#include "gameplay/Collision.h"
#include "gameplay/State.h"
#include "glm/gtx/dual_quaternion.hpp"
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
  const auto notWalking = map.down == GLFW_RELEASE && map.up == GLFW_RELEASE &&
                          map.left == GLFW_RELEASE && map.right == GLFW_RELEASE;
  if (notWalking) {
    return std::nullopt;
  }

  return new PlayerStates::WalkingState(entity);
}

// Walking state
std::optional<PlayerStates::PlayerState *>
PlayerStates::WalkingState::handleInput(InputKeymap map) {
  const auto walking = map.down == GLFW_PRESS || map.up == GLFW_PRESS ||
                       map.left == GLFW_PRESS || map.right == GLFW_PRESS;
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

PlayerImplementation::PlayerImplementation() 
{
  
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

void PlayerImplementation::transition(
    std::optional<PlayerStates::PlayerState *> state) {
  if (state.has_value()) {
    delete this->state;
    this->state = state.value();
  }
}

void PlayerImplementation::update(float dt) {
  const glm::vec3 cameraPos = glm::vec3{position.x, height, position.z};
  camera->setPosition(cameraPos);
  std::cout << "Player pos: "<< glm::to_string(position) << " state: " << state->toString() << std::endl;
}

// Todo normalize with camera direction
void PlayerImplementation::forward() {
  auto newDir = glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;

  std::cout << glm::to_string(newPos) << std::endl;

  position += newPos;

}
void PlayerImplementation::backward() {
  auto newDir = glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;

  std::cout << glm::to_string(newPos) << std::endl;

  position -= newPos;
}
void PlayerImplementation::left() {
  auto newDir = glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().y);
  auto newPos = glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;

  std::cout << glm::to_string(newPos) << std::endl;

  position -= newPos;
}
void PlayerImplementation::right() {
  auto newDir = glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().y);
  auto newPos = glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;

  std::cout << glm::to_string(newPos) << std::endl;

  position += newPos;
}

void PlayerImplementation::draw() {}

void PlayerImplementation::onCollide(Collision::Collisionable &other) {
  // Todo implement collision logic
}
