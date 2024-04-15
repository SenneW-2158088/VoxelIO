#pragma once

namespace noise {
// Basic class for generating a permutation
class Permutation {
  static const int default_size = 256;

  const unsigned char *table;
  const int size;

  Permutation(const unsigned char *table, const int size) : table{table}, size{size} {};

public:
  Permutation(const Permutation &) = delete;
  Permutation &operator=(const Permutation &) = delete;
  ~Permutation() { delete[] table; }

  static Permutation generate(); // Default to a 16 byte permutation table
  static Permutation generate(int size);

  inline char operator[](int index) const { return table[index]; };

public:
  inline int getSize() const { return size; };
};

class Noise {
protected:
  template <typename T> static constexpr auto lerp(T a, T b, T t) -> T {
    return a + t * (b - a);
  }

  template <typename T> static constexpr auto floor(T x) -> int {
    auto const xi = int(x);
    return (x < T(xi)) ? xi - 1 : xi;
  }

  template <typename T> static constexpr auto fade(T t) -> T {
    return t * t * t * (t * (t * T(6.0) - T(15.0)) + T(10.0));
  }
  static double gradient(int hash, double xf);
  static double gradient(int hash, double xf, double yf);

public:
  Noise() = default;
  virtual ~Noise() = default;
  virtual double noise(double) const = 0;
  virtual double noise(double, double) const = 0;
};

class Perlin : public Noise {
private:
  Permutation permutation;
public:
  Perlin();
  Perlin(int size);
  ~Perlin() = default;
  double noise(double x) const override;
  double noise(double x, double y) const override;
};
} // namespace Noise
