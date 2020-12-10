#include <core/solver.h>

#include <iostream>

using namespace cubesolver;

int main() {
  Solver solver;

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

  Cube scrambled(stickers);
  std::cout << "Searching..." << std::endl;

  std::vector<Move> solution = solver.SolveCube(scrambled);
  std::cout << "Solution: ";
  for (Move move: solution) {
    std::cout << MoveToString(move) << " ";
  }

  return 0;
}