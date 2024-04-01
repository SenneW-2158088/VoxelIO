//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_PLAYER_H
#define VOXELIO_PLAYER_H

#include <model/Entity.h>
#include <gameplay/Command.h>
#include <gameplay/State.h>
#include <manager/InputManager.h>


/**
 * @brief Interface for the player class.
 */
class Player : public Entity, public InputListener {
};

/**
 * @brief States for the player.
 */
namespace PlayerStates {
    class PlayerState : public BaseState<Player> {
    };

    class IdleState : public PlayerState {

    };

    class WalkingState : public PlayerState {

    };

    class RunningState : public PlayerState {

    };

    class JumpingState : public PlayerState {

    };
}


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
}

/**
 * @brief Implementation of the player class.
 */
class PlayerImplementation : public Player {
private:
    const float speed = -1.1f;
protected:
    void transition(PlayerStates::PlayerState *state);

    void onKeyPressed(int key) override;

public:
    void update(float dt) override;

    void draw() override;
};

#endif //VOXELIO_PLAYER_H
