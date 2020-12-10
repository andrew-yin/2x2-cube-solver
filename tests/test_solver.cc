#include "core/solver.h"

#include <catch2/catch.hpp>

using namespace cubesolver;

Solver solver;

TEST_CASE("Pre-solved cube") {
  Cube cube(green, white, orange);

  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution.empty());
}

TEST_CASE("Cube that is one move from being solved") {
  Cube cube(green, white, orange);
  cube.MoveB();

  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({Bp}));
}

TEST_CASE("Random scramble") {
  /* U F' R' U R2 F' R2 F */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[front][up_left] = blue;
  stickers[front][up_right] = orange;
  stickers[front][low_left] = red;
  stickers[front][low_right] = red;
  stickers[right][up_left] = yellow;
  stickers[right][up_right] = green;
  stickers[right][low_left] = blue;
  stickers[right][low_right] = white;
  stickers[up][up_left] = blue;
  stickers[up][up_right] = white;
  stickers[up][low_left] = orange;
  stickers[up][low_right] = green;
  stickers[left][up_left] = red;
  stickers[left][up_right] = white;
  stickers[left][low_left] = orange;
  stickers[left][low_right] = green;
  stickers[back][up_left] = red;
  stickers[back][up_right] = white;
  stickers[back][low_left] = green;
  stickers[back][low_right] = blue;
  stickers[down][up_left] = yellow;
  stickers[down][up_right] = yellow;
  stickers[down][low_left] = yellow;
  stickers[down][low_right] = orange;

  Cube cube(stickers);
  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({Bp, D2, B, R2, Dp, B, D, Rp}));
}

TEST_CASE("Invalid scramble") {
  /* Impossible corner color configurations */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[front][up_left] = yellow;
  stickers[front][up_right] = yellow;
  stickers[front][low_left] = yellow;
  stickers[front][low_right] = yellow;
  stickers[right][up_left] = white;
  stickers[right][up_right] = white;
  stickers[right][low_left] = white;
  stickers[right][low_right] = white;
  stickers[up][up_left] = blue;
  stickers[up][up_right] = blue;
  stickers[up][low_left] = blue;
  stickers[up][low_right] = blue;
  stickers[left][up_left] = green;
  stickers[left][up_right] = green;
  stickers[left][low_left] = green;
  stickers[left][low_right] = green;
  stickers[back][up_right] = red;
  stickers[back][low_left] = red;
  stickers[back][low_right] = red;
  stickers[down][up_left] = orange;
  stickers[down][up_right] = orange;
  stickers[down][low_left] = orange;
  stickers[down][low_right] = orange;

  Cube cube(stickers);
  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({no_move}));
}