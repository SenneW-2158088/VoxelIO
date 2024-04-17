#include "Noise.h"
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>

using namespace noise;

Permutation Permutation::generate() {
  unsigned char *table = new unsigned char[default_size * 2];

  for (int i = 0; i < default_size; ++i) {
    table[i] = static_cast<char>(i);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(table, table + default_size, std::default_random_engine(seed));

  memcpy(table + default_size, table, default_size * sizeof(char));

  return Permutation(table, default_size);
};

Permutation Permutation::generate(int size) {
  unsigned char *table = new unsigned char[size * 2];

  for (int i = 0; i < size; ++i) {
    table[i] = static_cast<char>(i);
  }

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(table, table + size, std::default_random_engine(seed));

  memcpy(table + size, table, size * sizeof(char));

  return Permutation(table, size);
}


double Noise::gradient(int hash, double xf) {
  return (hash & 0x1) ? xf : -xf;
}

double Noise::gradient(int hash, double xf, double yf) {
  switch (hash & 0x7) {
  case 0x0:
    return xf + yf;
  case 0x1:
    return xf;
  case 0x2:
    return xf - yf;
  case 0x3:
    return -yf;
  case 0x4:
    return -xf - yf;
  case 0x5:
    return -xf;
  case 0x6:
    return -xf + yf;
  case 0x7:
    return yf;
  default:
    return 0.0;
  }
}

Perlin::Perlin() : permutation(Permutation::generate()) {}
Perlin::Perlin(int size) : permutation(Permutation::generate(size)) {}

double Perlin::noise(double x) const {
  // Left coordinate of the unit-line that contains the input.
  int const xi0 = floor(x);

  // Input location in the unit-line.
  double const xf0 = x - double(xi0);
  double const xf1 = xf0 - double(1.0);

  // Wrap to range 0-255.
  int const xi = xi0 & permutation.getSize() - 1;

  // Apply the fade function to the location.
  double const u = fade(xf0);

  // Generate hash values for each point of the unit-line.
  int const h0 = permutation[xi + 0];
  int const h1 = permutation[xi + 1];

  // Linearly interpolate between dot products of each gradient with its
  // distance to the input location.
  return lerp(gradient(h0, xf0), gradient(h1, xf1), u);
}

double Perlin::noise(double x, double y) const {
  // doubleop-left coordinates of the unit-square.
  // int const xi0 = (int)floor(x) & (permutation.getSize() - 1);
  // int const yi0 = (int)floor(y) & (permutation.getSize() - 1);

  int const xi0 = floor(x);
  int const yi0 = floor(y);

  // Input location in the unit-square.
  double const xf0 = x - double(xi0);
  double const yf0 = y - double(yi0);
  double const xf1 = xf0 - double(1.0);
  double const yf1 = yf0 - double(1.0);

  // Wrap to range 0-255.
  int const xi = xi0 & (permutation.getSize() - 1);
  int const yi = yi0 & (permutation.getSize() - 1);

  // Apply the fade function to the location.
  double const u = fade(xf0);
  double const v = fade(yf0);

  // Generate hash values for each permutationoint of the unit-square.
  int const h00 = permutation[permutation[xi + 0] + yi + 0];
  int const h01 = permutation[permutation[xi + 0] + yi + 1];
  int const h10 = permutation[permutation[xi + 1] + yi + 0];
  int const h11 = permutation[permutation[xi + 1] + yi + 1];

  // Linearly interpolate between dot products of each gradient with its
  // distance to the input location.
  double const x1 = lerp(gradient(h00, xf0, yf0), gradient(h10, xf1, yf0), u);
  double const x2 = lerp(gradient(h01, xf0, yf1), gradient(h11, xf1, yf1), u);
  return lerp(x1, x2, v);
}
