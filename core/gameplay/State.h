//
// Created by Senne Wertelaers on 28/03/2024.
//

#ifndef VOXELIO_STATE_H
#define VOXELIO_STATE_H

#include "manager/InputManager.h"
#include <optional>

/**
 * Base class for all states
 */
template <class T, class S> class BaseState {
protected:
  T *entity;

public:
  explicit BaseState(T *entity) : entity(entity) {}
  virtual ~BaseState() = default;

  virtual std::optional<S *> handleInput(InputKeymap map) = 0;

  virtual void onEnter() = 0;

  virtual void onExit() = 0;
};

// state tells

#endif // VOXELIO_STATE_H
