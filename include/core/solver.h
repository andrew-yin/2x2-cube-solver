#pragma once

#include <string>
#include <vector>

#include "cube.h"
#include "move.h"

namespace cubesolver {

/**
 * A control class used to solve the Rubik's cube based on BFS and implicit
 * graph generation
 */
class Solver {
 public:
  /**
   * Solves the given Rubik's cube.
   *
   * @param scrambled_cube  The scrambled cube to be solved.
   * @return                A vector of moves needed to solve the Rubik's cube.
   *                        The i-th index represents the (i+1)-th move to
   *                        do to the scrambled cube to solve it.
   */
  std::vector<Move> SolveCube(const Cube& scrambled_cube) const;

 private:
  /**
   * Various methods used to determine if the given move is a move that
   * manipulates a certain face. For example, U, U', and U2 are all "Up" moves.
   *
   * @param move  The move to be determined
   * @return      True if the move manipulates the face, false otherwise
   */
  bool IsFrontMove(const Move& move) const;
  bool IsRightMove(const Move& move) const;
  bool IsLeftMove(const Move& move) const;
  bool IsUpMove(const Move& move) const;
  bool IsBackMove(const Move& move) const;
  bool IsDownMove(const Move& move) const;
};

}  // namespace cubesolver