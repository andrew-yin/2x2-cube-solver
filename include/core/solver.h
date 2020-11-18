#pragma once

#include <string>
#include "cube.h"
namespace cubesolver {

class Solver {
 public:
  static std::string SolveCube(Cube cube);
};

}