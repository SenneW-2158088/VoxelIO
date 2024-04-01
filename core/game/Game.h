//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_GAME_H
#define VOXELIO_GAME_H

#include <engine/GameEngine.h>

class Game {
protected:
    GameEngine* engine;
public:
    Game();
    void start();
};


#endif //VOXELIO_GAME_H
