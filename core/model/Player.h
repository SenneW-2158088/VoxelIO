//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_PLAYER_H
#define VOXELIO_PLAYER_H

#include <model/Entity.h>

class Player : public Entity {
private:
    const float speed = 0.1f;
protected:
public:
    void update(float dt) override;

    void draw() override;
};


#endif //VOXELIO_PLAYER_H
