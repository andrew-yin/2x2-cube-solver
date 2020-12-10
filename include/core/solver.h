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
  kF,
  kFPrime,
  kF2,
  kB,
  kBPrime,
  kB2,
  kU,
  kUPrime,
  kU2,
  kD,
  kDPrime,
  kD2,
  kR,
  kRPrime,
  kR2,
  kL,
  kLPrime,
  kL2,
  kNoMove
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
   * The graph is implicitly generated and is searched for a solution via BFS.
   *
   * The graph has two starting nodes - The first node is a solved state in the
   * same orientation as the front-upper-left corner of the Rubik's cube. This
   * reduces the search space immensely since we no longer need to consider the
   * 24 "distinct" orientations of the same scramble. The second node is the
   * scrambled state given.
   *
   * BFS then proceeds from both of these two nodes simultaneously. We are
   * careful not to generate scrambles from unnecessary moves by ensuring the
   * same face is not manipulated twice in a row. For example, doing an F move
   * directly followed by an F2 is redundant, since we could have simply done a
   * single F' move to achieve that state.
   *
   * BFS stops when the two generated graphs intersect at a common state. The
   * solution is then outputted by backtracking through both paths to get to
   * this state.
   *
   * @param scrambled_cube  The scrambled cube to be solved.
   * @return                A vector of moves needed to solve the Rubik's cube.
   *                        The i-th index represents the (i+1)-th move to
   *                        do to the scrambled cube to solve it.
   */
  std::vector<Move> SolveCube(Cube scrambled_cube) const;

 private:
  /**
   * Various methods used to determine if the given move is a move that
   * manipulates a certain face. For example, U, U', and U2 are all "Up" moves.
   *
   * @param move  The move to be determined
   * @return      True if the move manipulates the face, false otherwise
   */
  bool IsBackMove(const Move& move) const;
  bool IsRightMove(const Move& move) const;
  bool IsDownMove(const Move& move) const;

  /**
   * Checks if the cube given is actually a valid type of cube
   *
   * @param cube  The cube to be checked for validity
   * @return      True if the cube is a valid scramble, false otherwise
   */
  bool IsValidCube(const Cube& cube) const;

  /**
   * Checks if the corner given is a valid corner of the cube
   *
   * @param color1/2/3  The three colors of the corner
   * @return            True if the corner is valid, false otherwise
   */
  bool IsValidCorner(const Color& color1, const Color& color2,
                     const Color& color3) const;
};

}  // namespace cubesolver