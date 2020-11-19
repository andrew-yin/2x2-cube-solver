#pragma once

#include <vector>
#include <string>

#include "cube.h"

namespace cubesolver {

class Solver {
 public:
  std::vector<std::string> SolveCube(const Cube& scrambled_cube);
};

}