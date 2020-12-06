#pragma once

#include <string>
#include <vector>

#include "cube.h"

namespace cubesolver {

/**
 * A representation of the 18 (3 per face, 6 faces) possible singular moves
 * one can do to the Rubik's cube.
 *
 * More info can be found here: https://ruwix.com/the-rubiks-cube/notation/
 */
enum Move {
  F,
  Fp,
  F2,
  B,
  Bp,
  B2,
  U,
  Up,
  U2,
  D,
  Dp,
  D2,
  R,
  Rp,
  R2,
  L,
  Lp,
  L2,
  no_move
};

/**
 * Converts the given Move enum into a string.
 *
 * @param move  The move to be converted
 * @return      A string corresponding to the given move.
 */
std::string MoveToString(const Move& move);

/**
 * A control class used to solve the Rubik's cube based on BFS and implicit
 * graph generation
 */
class Solver {
 public:
  /**
   * Solves the given Rubik's cube.
   *
   * Algorithm overview:
   *
   * The graph is implicitly generated starting from a solved Rubik's cube and
   * is searched for a solution via BFS.
   *
   * The graph has two starting nodes - A solved state in the same orientation
   * as the front-upper-left corner of the Rubik's cube and the bottom-lower-right
   * corner of the cube. This reduces the search space immensely since we no
   * longer need to consider the 24 "distinct" orientations of the same scramble.
   * We also start from two opposite corners to increase the probability of
   * finding a solution in reasonable time.
   *
   * BFS then proceeds from these two nodes. We are careful not to generate
   * scrambles from unnecessary moves by ensuring the same face is not
   * manipulated twice in a row. For example, doing an F move directly followed
   * by an F2 is redundant, since we could have simply done a single F' move
   * to achieve that state.
   *
   * BFS stops when the node traversed onto is the same as the scramble given.
   * The solution then is returned by returning the reverse of the path needed
   * to go from solved to that state.
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
  bool IsBackMove(const Move& move) const;
  bool IsRightMove(const Move& move) const;
  bool IsLeftMove(const Move& move) const;
  bool IsUpMove(const Move& move) const;
  bool IsDownMove(const Move& move) const;
};

}  // namespace cubesolver