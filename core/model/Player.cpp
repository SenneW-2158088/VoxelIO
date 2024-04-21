//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Player.h"
#include "GLFW/glfw3.h"
#include "gameplay/Collision.h"
#include "gameplay/State.h"
#include "glm/geometric.hpp"
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
  if (map.up == GLFW_PRESS)
    entity->forward();
  if (map.left == GLFW_PRESS)
    entity->left();
  if (map.down == GLFW_PRESS)
    entity->backward();
  if (map.right == GLFW_PRESS)
    entity->right();

  if (walking) {
    return std::nullopt;
  }

  return new IdleState(entity);
}

// Jumping state
std::optional<PlayerStates::PlayerState *>
PlayerStates::JumpingState::handleInput(InputKeymap map) {
  return std::nullopt;
}

// Running state
std::optional<PlayerStates::PlayerState *>
PlayerStates::RunningState::handleInput(InputKeymap map) {
  return std::nullopt;
}

PlayerImplementation::PlayerImplementation() {

  PerspectiveCamera *camera =
      PerspectiveCameraBuilder()
          .setPosition(glm::vec3{position.x, height, position.z})
          ->setDirection(
              glm::vec3{0.f, 0.f, -1.f}) // looking forward in z direction
          ->setField(45.f)
          ->setAspect(16.f / 9.f)
          ->build();

  this->camera = camera;

  state = new PlayerStates::IdleState(this);

  Collision::Collisioner *collisioner = new Collision::Collisioner(
      this,
      new Collision::AABoundingBox(this->position, glm::vec3{-.2f, 0.f, -.2f},
                                   glm::vec3{.2f, height, .2f}),
      "Player bounding box");

  addCollsioner(collisioner);
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
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(this->position);
  }
}

// Todo normalize with camera direction
void PlayerImplementation::forward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  position += newPos;
}
void PlayerImplementation::backward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  position -= newPos;
}
void PlayerImplementation::left() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  position -= newPos;
}
void PlayerImplementation::right() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  position += newPos;
}

void PlayerImplementation::draw() {}

void PlayerImplementation::onCollide(const Collision::Collisioner &own,
                                     const Collision::Collisioner &other) {

  std::cout << "Player bounding box: " << own.getTag() << " collided with" << other.getTag() << std::endl;

  auto p = own.getBoundingBox()->calculatePenetration(*other.getBoundingBox());

  std::cout << glm::to_string(p) << std::endl;

  // calculate penetration

  auto dotx = glm::dot(own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter(), {1, 0, 0});

  auto dotz = glm::dot(own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter(), {0, 0, 1});

  std::cout << "DotX: " << glm::dot(own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter(), {1, 0, 0}) << std::endl;
  std::cout << "DotY: " << glm::dot(own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter(), {0, 1, 0}) << std::endl;
  std::cout << "DotZ: " << glm::dot(own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter(), {0, 0, 1}) << std::endl;

  if(abs(dotx) > abs(dotz)) {
    auto sign = (dotx > 0) ? 1.f : -1.f;
    std::cout << "Apply: " << glm::to_string(sign * glm::vec3{p.x, 0, 0}) << std::endl;
    position += sign * glm::vec3{p.x, 0, 0};
  }
  else{
    auto sign = (dotz > 0) ? 1.f : -1.f;
    std::cout << "Apply: " << glm::to_string(sign * glm::vec3{0, 0, p.z}) << std::endl;
    position += sign * glm::vec3{0, 0, p.z};
  }

  // apply inverse force to player
}
