//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Player.h"
#include "GLFW/glfw3.h"
#include "gameplay/Collision.h"
#include "gameplay/State.h"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
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
  if (map.space == GLFW_PRESS)
    entity->jump();

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

  // position += correction;
  std::cout << "Correction: " << glm::to_string(correction) << std::endl;
  std::cout << "Max Dots: " << glm::to_string(max_dots) << std::endl;
  std::cout << "Min Dots: " << glm::to_string(min_dots) << std::endl;
  std::cout << "Dots: " << glm::to_string(dots) << std::endl;

  // We use the sign of x
  auto abs_x = abs(dots.x);
  auto abs_z = abs(dots.z);

  std::cout << "Absx: " << abs_x << std::endl;
  std::cout << "Absz: " << abs_z << std::endl;

  auto sign_x = (min_dots.x * max_dots.x) < 0 ? -1 : 1;
  auto sign_z = (min_dots.z * max_dots.z) < 0 ? -1 : 1;

  std::cout << "Signx: " << sign_x << std::endl;
  std::cout << "Signz: " << sign_z << std::endl;

  auto use_x = (min_dots.x * max_dots.x) >= 0 ? true : false;
  auto use_z = (min_dots.z * max_dots.z) >= 0 ? true : false;

  auto signx = (dots.x > 0) ? 1.f : -1.f;
  auto signz = (dots.z > 0) ? 1.f : -1.f;

  correction.x *= signx;
  correction.z *= signz;

  if (abs_x >= abs_z) {
    std::cout << "use x" << std::endl;
    // apply x-correction
    position += glm::vec3{correction.x, 0, 0};
    if (sign_x < 0) {
      std::cout << "and z" << std::endl;
      position += glm::vec3{0, 0, correction.z};
    }
  } else {
    std::cout << "use z" << std::endl;
    // apply z-correction
    position += glm::vec3{0, 0, correction.z};
    if (sign_z < 0) {
      std::cout << "and x" << std::endl;
      position += glm::vec3{correction.x, 0, 0};
    }
  }

  // if(abs(dots.x) > abs(dots.z)) {
  //   auto sign = (dots.x > 0) ? 1.f : -1.f;
  //   position += sign * glm::vec3{correction.x, 0, 0};
  // }
  // else {
  //   auto sign = (dots.z > 0) ? 1.f : -1.f;
  //   position += sign * glm::vec3{0, 0, correction.z};
  // }

  // auto signx = (dots.x > 0) ? 1.f : -1.f;
  // position += signx * glm::vec3{correction.x, 0, 0};

  // auto signz = (dots.z > 0) ? 1.f : -1.f;
  // position += signz * glm::vec3{0, 0, correction.z};

  this->correction = glm::vec3{0, 0, 0};
  this->dots = glm::vec3{0};
  this->max_dots = glm::vec3{0};
  this->min_dots = glm::vec3{0};

  const glm::vec3 cameraPos = glm::vec3{position.x, position.y + height, position.z};
  camera->setPosition(cameraPos);

  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}

// Todo normalize with camera direction
void PlayerImplementation::forward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  position += newPos;

  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}
void PlayerImplementation::backward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  position -= newPos;
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}
void PlayerImplementation::left() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  position -= newPos;
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}
void PlayerImplementation::right() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  position += newPos;
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}

void PlayerImplementation::jump() {
  std::cout << "Jumping" << std::endl;
  position += glm::vec3{0.f, 1.f, 0.1} * speed;
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}

void PlayerImplementation::draw() {}

void PlayerImplementation::onCollide(const Collision::Collisioner &own,
                                     const Collision::Collisioner &other) {

  auto p = own.getBoundingBox()->calculatePenetration(*other.getBoundingBox());
  auto dotx = glm::dot(own.getBoundingBox()->getCenter() -
                           other.getBoundingBox()->getCenter(),
                       {1, 0, 0});
  auto dotz = glm::dot(own.getBoundingBox()->getCenter() -
                           other.getBoundingBox()->getCenter(),
                       {0, 0, 1});

  dots += glm::vec3{dotx, 0, dotz};
  max_dots = glm::max({dotx, 0, dotz}, max_dots);
  min_dots = glm::min({dotx, 0, dotz}, min_dots);

  if (abs(dotx) > abs(dotz)) {
    correction = glm::max(glm::vec3{p.x, 0, 0}, correction);
  } else {
    correction = glm::max(glm::vec3{0, 0, p.z}, correction);
  }

  // apply inverse force to player
}
