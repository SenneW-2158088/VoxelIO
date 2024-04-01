//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_STATE_H
#define VOXELIO_STATE_H

#include <optional>
#include <model/Player.h>

/**
 * Base class for all states
 */
template<class T>
class BaseState {
protected:
    T* entity;
public:
    explicit BaseState(T* entity) : entity(entity) {}
    virtual ~BaseState() = default;

    virtual void handleInput() = 0;

    virtual void onEnter() = 0;

    virtual void onExit() = 0;
};

// state tells

#endif //VOXELIO_STATE_H
