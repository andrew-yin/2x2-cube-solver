#pragma once

#include <array>

#include "color.h"

namespace cubesolver {

const size_t kNumFaces = 6;
const size_t kNumCornersPerFace = 4;

struct Cube {
  Cube();
  Cube(const Color& front_col, const Color& up_col, const Color& left_col);
  Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
           stickers);

  void MoveD();
  void MoveR();
  void MoveB();

  bool operator==(const Cube& b) const;

  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers_;

 private:
  Color GetOppositeSide(const Color& color) const;
};

}  // namespace cubesolver