//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_PLAYER_H
#define VOXELIO_PLAYER_H

#include <model/Entity.h>
#include <gameplay/Command.h>
#include <gameplay/State.h>

class Player : public Entity {
private:
    const float speed = 0.1f;
protected:
    void handleInput();
public:
    Player() = default;
    void update(float dt) override;

    void draw() override;
};

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


#endif //VOXELIO_PLAYER_H
