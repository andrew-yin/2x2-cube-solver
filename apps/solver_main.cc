#include <core/corner.h>
#include <core/face.h>
#include <core/solver.h>

#include <iostream>

using namespace cubesolver;

int main() {
  Solver solver;

  /* Scramble: R U2 L' B D */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;

  stickers[front][up_left] = yellow;
  stickers[front][up_right] = blue;
  stickers[front][low_left] = white;
  stickers[front][low_right] = orange;

  stickers[right][up_left] = orange;
  stickers[right][up_right] = blue;
  stickers[right][low_left] = yellow;
  stickers[right][low_right] = yellow;

  stickers[up][up_left] = orange;
  stickers[up][up_right] = red;
  stickers[up][low_left] = green;
  stickers[up][low_right] = white;

  stickers[left][up_left] = white;
  stickers[left][up_right] = orange;
  stickers[left][low_left] = green;
  stickers[left][low_right] = green;

  stickers[back][up_left] = white;
  stickers[back][up_right] = green;
  stickers[back][low_left] = red;
  stickers[back][low_right] = yellow;

  stickers[down][up_left] = red;
  stickers[down][up_right] = blue;
  stickers[down][low_left] = red;
  stickers[down][low_right] = blue;

  Cube scrambled(stickers);
  std::cout << "Searching..." << std::endl;

  std::vector<Move> solution = solver.SolveCube(scrambled);
  std::cout << "Solution: ";
  for (Move move: solution) {
    std::cout << MoveToString(move) << " ";
  }

  return 0;
}