//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_PLAYER_H
#define VOXELIO_PLAYER_H

#include "gameplay/Collision.h"
#include "glm/fwd.hpp"
#include "model/Camera.h"
#include <gameplay/Command.h>
#include <gameplay/State.h>
#include <manager/InputManager.h>
#include <model/Entity.h>
#include <string>

/**
 * @brief Interface for the player class.
 */
class Player : public Entity, public InputListener, public Collision::Collisionable{
public:
  Player() = default;
  virtual Camera *getCamera() const = 0;
  void onInput(InputKeymap map) override = 0;
  void onCollide(const Collision::Collisioner &other) override = 0;

  std::string getName() const override { return "Player"; };

  virtual void forward() = 0;
  virtual void backward() = 0;
  virtual void left() = 0;
  virtual void right() = 0;
};

/**
 * @brief States for the player.
 */
namespace PlayerStates {
class PlayerState : public BaseState<Player, PlayerState> {
public:
  PlayerState(Player* player);
  std::optional<PlayerState *> handleInput(InputKeymap map) override = 0;
  virtual void onEnter() override{};
  virtual void onExit() override{};

  virtual std::string toString() const = 0; 
};

class IdleState : public PlayerState {
public:
  IdleState(Player* player) : PlayerState(player){}
  std::optional<PlayerState *> handleInput(InputKeymap map) override;
  std::string toString() const override { return "Idle";};
};

class WalkingState : public PlayerState {
public:
  WalkingState(Player* player) : PlayerState(player){}
  std::optional<PlayerState *> handleInput(InputKeymap map) override;
  std::string toString() const override { return "Walking";};
};

class RunningState : public PlayerState {
public:
  RunningState(Player* player) : PlayerState(player){}
  std::optional<PlayerState *> handleInput(InputKeymap map) override;
  std::string toString() const override { return "Running";};
};

class JumpingState : public PlayerState {
public:
  JumpingState(Player* player) : PlayerState(player){}
  std::optional<PlayerState *> handleInput(InputKeymap map) override;
  std::string toString() const override { return "Jumping";};
};
} // namespace PlayerStates

/**
 * @brief Command to move the player in a certain direction.
 */
namespace PlayerCommands {

class MoveCommand : public Command<Player> {
private:
  glm::vec3 direction;

public:
  MoveCommand(glm::vec3 direction) : direction(direction) {}

  void execute(Player *player) override {
    player->setPosition(player->getPosition() + direction);
  }

  void undo(Player *player) override {
    player->setPosition(player->getPosition() - direction);
  }
};
} // namespace PlayerCommands

/**
 * @brief Implementation of the player class.
 */
class PlayerImplementation : public Player {
private:
  const float height = 1.8f;
  const float speed = 0.05f;

  Camera *camera;
  PlayerStates::PlayerState *state;

protected:
  void transition(std::optional<PlayerStates::PlayerState *> state);

public:
  PlayerImplementation();
  void update(float dt) override;
  void onInput(InputKeymap map) override;

  void draw() override;
  
  void forward() override;
  void backward() override;
  void left() override;
  void right() override;


public:
  Camera *getCamera() const override { return camera; };
  void onCollide(const Collision::Collisioner &other) override;
};

#endif // VOXELIO_PLAYER_H
