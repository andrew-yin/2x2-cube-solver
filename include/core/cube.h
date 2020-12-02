#pragma once

#include <array>

#include "color.h"

namespace cubesolver {

const size_t kNumFaces = 6;
const size_t kNumCornersPerFace = 4;

struct Cube {
  Cube();
  Cube(const Color& front_back_col, const Color& up_down_col, const Color& left_right_col, bool is_ful);
  explicit Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
           stickers);

  void MoveU();
  void MoveD();
  void MoveR();
  void MoveL();
  void MoveF();
  void MoveB();

  bool operator==(const Cube& b) const;

  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers_;

 private:
  Color GetOppositeSide(const Color& color) const;
};

}  // namespace cubesolver