#pragma once

#include <vector>
#include <string>

#include "cube.h"

namespace cubesolver {

class Solver {
 public:
  std::vector<std::string> SolveCube(const Cube& scrambled_cube) const;

 private:
  bool IsFrontMove(const std::string& move) const;
  bool IsRightMove(const std::string& move) const;
  bool IsLeftMove(const std::string& move) const;
  bool IsUpMove(const std::string& move) const;
  bool IsBackMove(const std::string& move) const;
  bool IsDownMove(const std::string& move) const;
};

}