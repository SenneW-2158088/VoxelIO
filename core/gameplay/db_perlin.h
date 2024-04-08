/*
 * db-perlin - see license at the bottom, no warranty implied, use at your own
 * risk; made by daniilsjb (https://github.com/daniilsjb/perlin-noise)
 *
 * The following is an implementation of Ken Perlin's Improved Noise in 1D, 2D,
 * and 3D. This code has no external dependencies and as such may easily be used
 * as a library in other projects.
 *
 * I wrote this with the primary goal of having a bit of fun and learning more
 * about the famous algorithm used everywhere in procedural generation.
 * Ultimately, my goal was to use this implementation in several other projects
 * (it's always good to have a noise generator lying around). I hope it could be
 * useful to other people, too!
 *
 * Usage:
 *
 * This code is written as a single-header library using the same technique as
 * stb libraries. There must be exactly one source file (C++) which defines
 * symbol `DB_PERLIN_IMPL` before including this header. You may place such
 * implementation in a dedicated file:
 *
 * ```cpp
 * #define DB_PERLIN_IMPL
 * #include "db_perlin.hpp"
 * ```
 *
 * Compile that file together with the rest of the program, and all other files
 * may then simply include this header without any additional work.
 *
 * To generate noise, simply use the `perlin` function under `db` namespace.
 * There are three overloads accounting for each dimension, so pass 1-3
 * arguments to generate noise in the corresponding number of dimensions.
 *
 * The implementation has template specializations to work with either floats or
 * doubles, depending on the desired accuracy.
 */

#pragma once

namespace db {
template <typename T> constexpr auto perlin(T x) -> T;

template <typename T> constexpr auto perlin(T x, T y) -> T;

template <typename T> constexpr auto perlin(T x, T y, T z) -> T;
} // namespace db

/*
MIT License

Copyright (c) 2020-2024 Daniils Buts

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
