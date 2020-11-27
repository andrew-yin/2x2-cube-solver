#pragma once

#include <array>

#include "color.h"

namespace cubesolver {

const size_t kNumFaces = 6;
const size_t kNumCornersPerFace = 4;

struct Cube {
  Cube();
  Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
           stickers);

  void MoveU();
  void MoveD();
  void MoveL();
  void MoveR();
  void MoveB();
  void MoveF();

  bool operator==(const Cube& b) const;

  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers_;
};

}  // namespace cubesolver