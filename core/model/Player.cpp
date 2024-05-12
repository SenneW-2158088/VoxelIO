//
// Created by Senne Wertelaers on 28/03/2024.
//

#include "Player.h"
#include "GLFW/glfw3.h"
#include "gameplay/Collision.h"
#include "gameplay/State.h"
#include "glm/common.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/dual_quaternion.hpp"
#include "manager/AssetManager.h"
#include "manager/InputManager.h"
#include "model/Camera.h"
#include "model/CrossHair.hpp"
#include "model/Voxel.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <optional>

PlayerStates::PlayerState::PlayerState(Player *player)
    : BaseState<Player, PlayerState>(player) {}

// Idle state
std::optional<PlayerStates::PlayerState *>
PlayerStates::IdleState::handleInput(InputKeymap map) {
  AssetManager::stopCurrentSound();
  const auto notWalking = map.down == GLFW_RELEASE && map.up == GLFW_RELEASE &&
                          map.left == GLFW_RELEASE && map.right == GLFW_RELEASE;
  if (notWalking) {
    return std::nullopt;
  }

  const auto running = map.shift == GLFW_PRESS;
  if(running){
    return new RunningState(entity);
  }

  return new PlayerStates::WalkingState(entity);
}

// Walking state
std::optional<PlayerStates::PlayerState *>
PlayerStates::WalkingState::handleInput(InputKeymap map) {
  AssetManager::playSound("footsteps.mp3");
  entity->setSpeed(Player::walking_speed);
  const auto walking = map.down == GLFW_PRESS || map.up == GLFW_PRESS ||
                       map.left == GLFW_PRESS || map.right == GLFW_PRESS;

  const auto running = map.shift == GLFW_PRESS;
  const auto jumping = map.space == GLFW_PRESS;
  
  if(jumping){
    entity->jump();
    return new JumpingState(entity);
  }

  if (map.up == GLFW_PRESS)
    entity->forward();
  if (map.left == GLFW_PRESS)
    entity->left();
  if (map.down == GLFW_PRESS)
    entity->backward();
  if (map.right == GLFW_PRESS)
    entity->right();
  

  if (walking) {
    if(running){
      return new RunningState(entity);
    }
    return std::nullopt;
  }

  return new IdleState(entity);
}

// Jumping state
std::optional<PlayerStates::PlayerState *>
PlayerStates::JumpingState::handleInput(InputKeymap map) {
  AssetManager::playSound("jump.mp3");
  entity->setSpeed(Player::walking_speed);
  const auto walking = map.down == GLFW_PRESS || map.up == GLFW_PRESS ||
                       map.left == GLFW_PRESS || map.right == GLFW_PRESS;

  const auto running = map.shift == GLFW_PRESS;
  const auto jumping = map.space == GLFW_PRESS;

  if(jumping){
    entity->jump();
    return std::nullopt;
  }

  if (map.up == GLFW_PRESS)
    entity->forward();
  if (map.left == GLFW_PRESS)
    entity->left();
  if (map.down == GLFW_PRESS)
    entity->backward();
  if (map.right == GLFW_PRESS)
    entity->right();

  if (walking) {
    if(running){
      return new RunningState(entity);
    }
    return new WalkingState(entity);
  }

  return new IdleState(entity);
  
}

// Running state
std::optional<PlayerStates::PlayerState *>
PlayerStates::RunningState::handleInput(InputKeymap map) {
  AssetManager::playSound("footsteps.mp3", 1.3f);
  entity->setSpeed(Player::running_speed);
  const auto walking = map.down == GLFW_PRESS || map.up == GLFW_PRESS ||
                       map.left == GLFW_PRESS || map.right == GLFW_PRESS;

  const auto running = map.shift == GLFW_PRESS;

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

  if(walking){
    if (running) {
      return std::nullopt;
    }

    return new WalkingState(entity);
  }
  
  return new IdleState(entity);
}

PlayerImplementation::PlayerImplementation() {


  PerspectiveCamera *camera =
      PerspectiveCameraBuilder()
          .setPosition(glm::vec3{position.x, position.y + height, position.z})
          ->setDirection(
              glm::vec3{0.f, 0.f, -1.f}) // looking forward in z direction
          ->setField(45.f)
          ->setAspect(16.f / 9.f)
          ->build();

  this->camera = camera;

  state = new PlayerStates::IdleState(this);

  this->boundingBox = new Collision::AABoundingBox(this->position, glm::vec3{-.2f, 0.f, -.2f}, glm::vec3{.2f, height, .2f});
  this->ray = new Collision::Ray(camera->getPosition(), camera->getDirection());

  Collision::Collisioner *bb_collisioner = new Collision::Collisioner(
      this,
      boundingBox,
      "boundingbox");

  // Ray
  Collision::Collisioner *ray_collisioner = new Collision::Collisioner(
      this,
      ray,
      "ray");

  
  this->crosshair = new CrossHair();

  addCollsioner(bb_collisioner);
  addCollsioner(ray_collisioner);
}

void PlayerImplementation::onInput(InputKeymap map) {
  if(map.interact == GLFW_PRESS && pickingobject.has_value()){
    if(pickingobject.has_value()){
      auto v = dynamic_cast<Voxel*>(pickingobject.value()->getEntity().value());
      if(v){
        v->destroy();
      }
      auto i = dynamic_cast<InstancedVoxel*>(pickingobject.value()->getEntity().value());
      if(i){
        i->destroy(pickingobject.value()->getBoundingBox()->getPosition());
      }
    }
  }

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


  // if(state){
  //   std::cout << state->toString() << std::endl;
  //   std::cout << speed << std::endl;
  // }
  auto signx = (dots.x > 0) ? 1.f : -1.f;
  auto signy = (dots.y > 0) ? 1.f : -1.f;
  auto signz = (dots.z > 0) ? 1.f : -1.f;

  if(position.y <= 0){
    position.y = 0;
    this->acceleration= glm::vec3{0};
  }
  else {
    if(correction.y <= 0){
      acceleration.y -= 9.81 * dt;
    }
    velocity.y += acceleration.y;
  }

  auto a = glm::abs(dots);
  auto sum = min_dots + max_dots;

  // std::cout << "Dots: " << glm::to_string(dots) << std::endl;
  // std::cout << "Max Dots: " << glm::to_string(max_dots) << std::endl;
  // std::cout << "Min Dots: " << glm::to_string(min_dots) << std::endl;
  // std::cout << "Sum Dots: " << glm::to_string(min_dots + max_dots) << std::endl;
  // std::cout << "Abs sum: " << glm::to_string(glm::abs(min_dots) + glm::abs(max_dots))  << std::endl;

  auto diffx = (sum.x < 0 && dots.x < 0) && (sum.x < 0 && dots.x < 0);
  auto diffz = (sum.z < 0 && dots.z < 0) && (sum.z < 0 && dots.z < 0);
  auto abss = glm::abs(min_dots) + glm::abs(max_dots);

  auto ax = a.x / a.z;
  auto az = a.z / a.x;
  // std::cout << "ax: "<< ax << std::endl;
  // std::cout << "az: "<< az << std::endl;

  if(a.z > a.x && ax + 0.4f < 1.f && az + 0.4f > 1) {
    // std::cout << "cx" << std::endl;
    correction.x = 0;
  }

  if(a.x > a.z && az + 0.4f < 1.f && ax + 0.4f > 1) {
    // std::cout << "cz" << std::endl;
    correction.z = 0;
  }

  position += velocity * dt;

  correction.x *= signx;
  correction.y *= signy;
  correction.z *= signz;

  position += correction;

  // Collision garbage
  this->correction = glm::vec3{0, 0, 0};
  this->dots = glm::vec3{0};
  this->max_dots = glm::vec3{0};
  this->min_dots = glm::vec3{0};

  // Physics garbage
  this->velocity = glm::vec3{0};
  // this->acceleration= glm::vec3{0};

  if(pickingobject.has_value()){
    auto v = dynamic_cast<Voxel*>(pickingobject.value()->getEntity().value());
    if(v){
      v->highlight();
    }
    auto i = dynamic_cast<InstancedVoxel*>(pickingobject.value()->getEntity().value());
    if(i){
      i->highlight(pickingobject.value()->getBoundingBox()->getPosition());
    }
  }
  
  const glm::vec3 cameraPos = glm::vec3{position.x, position.y + height, position.z};
  camera->setPosition(cameraPos);

  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }

  ray->setPosition(cameraPos);
  ray->setDirection(glm::normalize(camera->getDirection()));

  pickingobject.reset();

}

// Todo normalize with camera direction
void PlayerImplementation::forward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  velocity += newPos;
}
void PlayerImplementation::backward() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos = glm::normalize(newDir) * speed;
  velocity -= newPos;
}
void PlayerImplementation::left() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  velocity -= newPos;
}
void PlayerImplementation::right() {
  auto newDir =
      glm::vec3(camera->getDirection().x, 0.f, camera->getDirection().z);
  auto newPos =
      glm::normalize(glm::cross(newDir, glm::vec3{0.f, 1.f, 0.f})) * speed;
  velocity += newPos;
}

void PlayerImplementation::jump() {
  std::cout << "Jumping" << std::endl;
  velocity += glm::vec3{0.f, 10.f, 0.1};
  acceleration.y = 0;
  for (auto collisioner : getCollisioners()) {
    collisioner->getBoundingBox()->setPosition(position);
  }
}

void PlayerImplementation::draw() {
  this->crosshair->draw();
}

void PlayerImplementation::onCollide(const Collision::Collisioner &own,
                                     const Collision::Collisioner &other) {

  if(own.getTag() == "boundingbox") handleBlockCollision(own, other);
  if(own.getTag() == "ray") handleRayCollision(own, other);

}

void PlayerImplementation::handleBlockCollision(const Collision::Collisioner &own, const Collision::Collisioner &other) {
  
  auto p = own.getBoundingBox()->calculatePenetration(*other.getBoundingBox());


  // std::cout << "Center own: " << glm::to_string(own.getBoundingBox()->getCenter()) << std::endl;
  // std::cout << "Center other: " << glm::to_string(other.getBoundingBox()->getCenter()) << std::endl;

  auto other_size = other.getBoundingBox()->getSize();
  auto own_size = own.getBoundingBox()->getSize();

  float component_max = glm::max(glm::max(own_size.x, own_size.y), own_size.z);

  auto mul = glm::vec3{component_max} / component_max;

  glm::vec3 diff = own.getBoundingBox()->getCenter() - other.getBoundingBox()->getCenter() * mul;
  diff= glm::normalize(diff);

  float dotx = glm::dot(diff, glm::vec3{1.f, 0.f, 0.f});
  float doty = glm::dot(diff, glm::vec3{0.f, 1.f, 0.f});
  float dotz = glm::dot(diff, glm::vec3{0.f, 0.f, 1.f});


  // rescale center
  // std::cout << "Calculated dotx: " << dotx << std::endl;
  // std::cout << "Calculated doty: "<< doty << std::endl;
  // std::cout << "Calculated dotz: "<< dotz << std::endl;

  dots += glm::vec3{dotx, doty, dotz};

  // apply corrections idk
  if (std::abs(dotx) >= std::abs(dotz) && std::abs(dotx) >= std::abs(doty)) {
    correction = glm::max(glm::vec3{p.x, 0, 0}, correction);
    max_dots += glm::max(glm::vec3{0.f, doty, dotz}, glm::vec3{0.f, 0.f, 0.f});
    min_dots += glm::min(glm::vec3{0.f, doty, dotz}, glm::vec3{0.f, 0.f, 0.f});
  } 
  else if(std::abs(dotz) > std::abs(dotx) && std::abs(dotz) > std::abs(doty)) {
    correction = glm::max(glm::vec3{0, 0, p.z}, correction);
    max_dots += glm::max(glm::vec3{dotx, doty, 0.f}, glm::vec3{0.f, 0.f, 0.f});
    min_dots += glm::min(glm::vec3{dotx, doty, 0.f}, glm::vec3{0.f, 0.f, 0.f});
  }
  else {
    correction = glm::max(glm::vec3{0, p.y, 0}, correction);
    max_dots += glm::max(glm::vec3{dotx, 0.f, dotz}, glm::vec3{0.f, 0.f, 0.f});
    min_dots += glm::min(glm::vec3{dotx, 0.f, dotz}, glm::vec3{0.f, 0.f, 0.f});
  }
}

void PlayerImplementation::handleRayCollision(const Collision::Collisioner &own, const Collision::Collisioner &other) {

  if(pickingobject.has_value()){
    auto prev_distance = glm::length(pickingobject.value()->getBoundingBox()->getPosition() - ray->getPosition());
    auto new_distance = glm::length(other.getBoundingBox()->getPosition() - ray->getPosition());

    if(new_distance < prev_distance) {
      pickingobject = &other;
    }
  } else {
      pickingobject = &other;
  }
  
}

