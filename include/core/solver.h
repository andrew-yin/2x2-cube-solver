#pragma once

#include <string>
#include <vector>

#include "cube.h"
#include "move.h"

namespace cubesolver {

class Solver {
 public:
  std::vector<Move> SolveCube(const Cube& scrambled_cube) const;

 private:
  bool IsFrontMove(const Move& move) const;
  bool IsRightMove(const Move& move) const;
  bool IsLeftMove(const Move& move) const;
  bool IsUpMove(const Move& move) const;
  bool IsBackMove(const Move& move) const;
  bool IsDownMove(const Move& move) const;
};

}