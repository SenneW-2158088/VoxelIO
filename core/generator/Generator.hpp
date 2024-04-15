#pragma once

template <typename T, class P> class Generator {
public:
  virtual T *generate(P) const = 0;
};
