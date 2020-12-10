#include "core/solver.h"

#include <catch2/catch.hpp>

using namespace cubesolver;

Solver solver;

TEST_CASE("Pre-solved cube") {
  Cube cube(kGreen, kWhite, kOrange);

  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution.empty());
}

TEST_CASE("Cube that is one move from being solved") {
  Cube cube(kGreen, kWhite, kOrange);
  cube.MoveB();

  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({kBPrime}));
}

TEST_CASE("Random scramble") {
  /* U F' R' U R2 F' R2 F */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[kFront][kUpperLeft] = kBlue;
  stickers[kFront][kUpperRight] = kOrange;
  stickers[kFront][kLowerLeft] = kRed;
  stickers[kFront][kLowerRight] = kRed;
  stickers[kRight][kUpperLeft] = kYellow;
  stickers[kRight][kUpperRight] = kGreen;
  stickers[kRight][kLowerLeft] = kBlue;
  stickers[kRight][kLowerRight] = kWhite;
  stickers[kUp][kUpperLeft] = kBlue;
  stickers[kUp][kUpperRight] = kWhite;
  stickers[kUp][kLowerLeft] = kOrange;
  stickers[kUp][kLowerRight] = kGreen;
  stickers[kLeft][kUpperLeft] = kRed;
  stickers[kLeft][kUpperRight] = kWhite;
  stickers[kLeft][kLowerLeft] = kOrange;
  stickers[kLeft][kLowerRight] = kGreen;
  stickers[kBack][kUpperLeft] = kRed;
  stickers[kBack][kUpperRight] = kWhite;
  stickers[kBack][kLowerLeft] = kGreen;
  stickers[kBack][kLowerRight] = kBlue;
  stickers[kDown][kUpperLeft] = kYellow;
  stickers[kDown][kUpperRight] = kYellow;
  stickers[kDown][kLowerLeft] = kYellow;
  stickers[kDown][kLowerRight] = kOrange;

  Cube cube(stickers);
  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({kBPrime, kD2, kB, kR2, kDPrime, kB, kD, kRPrime}));
}

TEST_CASE("Invalid scramble") {
  /* Impossible corner color configurations */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[kFront][kUpperLeft] = kYellow;
  stickers[kFront][kUpperRight] = kYellow;
  stickers[kFront][kLowerLeft] = kYellow;
  stickers[kFront][kLowerRight] = kYellow;
  stickers[kRight][kUpperLeft] = kWhite;
  stickers[kRight][kUpperRight] = kWhite;
  stickers[kRight][kLowerLeft] = kWhite;
  stickers[kRight][kLowerRight] = kWhite;
  stickers[kUp][kUpperLeft] = kBlue;
  stickers[kUp][kUpperRight] = kBlue;
  stickers[kUp][kLowerLeft] = kBlue;
  stickers[kUp][kLowerRight] = kBlue;
  stickers[kLeft][kUpperLeft] = kGreen;
  stickers[kLeft][kUpperRight] = kGreen;
  stickers[kLeft][kLowerLeft] = kGreen;
  stickers[kLeft][kLowerRight] = kGreen;
  stickers[kBack][kUpperRight] = kRed;
  stickers[kBack][kLowerLeft] = kRed;
  stickers[kBack][kLowerRight] = kRed;
  stickers[kDown][kUpperLeft] = kOrange;
  stickers[kDown][kUpperRight] = kOrange;
  stickers[kDown][kLowerLeft] = kOrange;
  stickers[kDown][kLowerRight] = kOrange;

  Cube cube(stickers);
  std::vector<Move> solution = solver.SolveCube(cube);
  REQUIRE(solution == std::vector<Move>({kNoMove}));
}