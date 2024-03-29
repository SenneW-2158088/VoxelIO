//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_STATE_H
#define VOXELIO_STATE_H

#include <optional>
#include <model/Player.h>

class BaseState {
protected:
    Player* player;
public:
    explicit BaseState(Player* player) : player(player) {}
    virtual ~BaseState() = default;

    virtual void onEnter() = 0;

    virtual void onExit() = 0;
};

#endif //VOXELIO_STATE_H
