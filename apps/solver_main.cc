#include <core/solver.h>

#include <iostream>

using namespace cubesolver;

int main() {
  Solver solver;

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

  Cube scrambled(stickers);
  std::cout << "Searching..." << std::endl;

  std::vector<Move> solution = solver.SolveCube(scrambled);
  std::cout << "Solution: ";
  for (Move move: solution) {
    std::cout << MoveToString(move) << " ";
  }

  return 0;
}