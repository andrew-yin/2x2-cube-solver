#pragma once

#include <queue>
#include <string>
#include <unordered_map>
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
  Solver() = default;

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
   * solution is then outputted by backtracking through the two paths that lead
   * to this state.
   *
   * @param scrambled_cube  The scrambled cube to be solved.
   * @return                A vector of moves needed to solve the Rubik's cube.
   *                        The i-th index represents the (i+1)-th move to
   *                        do to the scrambled cube to solve it.
   */
  std::vector<Move> SolveCube(Cube scrambled_cube);

 private:
  /**
   * Queues and unordered maps used for BFS from the two starting nodes of
   * a solved state and the scrambled state
   */
  std::queue<std::pair<Cube, std::vector<Move>>> from_solved_queue_;
  std::unordered_map<ID, std::vector<Move>> past_from_solved_states_;

  std::queue<std::pair<Cube, std::vector<Move>>> from_scrambled_queue_;
  std::unordered_map<ID, std::vector<Move>> past_from_scrambled_states_;

  /**
   * Resets the instance of the Solver class to prepare for the next solve
   */
  void Reset();
  /**
   * Initializes the solver based on the scramble given
   *
   * @param scrambled_cube  The scramble given
   */
  void Initialize(const Cube& scrambled_cube);

  /**
   * Generates the next set of nodes for the graphs in BFS by manipulating the
   * back, right, and/or down faces of the current node
   *
   * @param from_solved_cube       The cube state of the current node from the
   *                               graph with the solved state starting node
   * @param from_solved_scramble   The scramble of the current node from the
   *                               graph with the solved state starting node
   * @param from_solved_last_move  The last move needed to reach the current
   *                               node from the graph with the solved state
   *                               starting node.
   *
   * (These params are analogous to the three above, except they come from
   *  the graph with the scrambled cube as the starting node)
   * @param from_scrambled_cube
   * @param from_scrambled_scramble
   * @param from_scrambled_last_move
   */
  void GenerateBackNodes(Cube& from_solved_cube,
                         std::vector<Move>& from_solved_scramble,
                         const Move& from_solved_last_move,
                         Cube& from_scrambled_cube,
                         std::vector<Move>& from_scrambled_scramble,
                         const Move& from_scrambled_last_move);
  void GenerateRightNodes(Cube& from_solved_cube, Cube& from_scrambled_cube,
                          std::vector<Move>& from_solved_scramble,
                          std::vector<Move>& from_scrambled_scramble,
                          const Move& from_solved_last_move,
                          const Move& from_scrambled_last_move);
  void GenerateDownNodes(Cube& from_solved_cube, Cube& from_scrambled_cube,
                         std::vector<Move>& from_solved_scramble,
                         std::vector<Move>& from_scrambled_scramble,
                         const Move& from_solved_last_move,
                         const Move& from_scrambled_last_move);

  /**
   * Combines the two scrambles given to obtain a final solution
   * @param from_solved_scramble     The set of moves needed to get to the
   *                                 current state from the solved cube
   * @param from_scrambled_scramble  The set of moves needed to get to the
   *                                 current state from the scrambled cube
   * @return                         The final solution computed by merging
   *                                 the two scrambles
   */
  std::vector<Move> GetSolution(
      std::vector<Move> from_solved_scramble,
      const std::vector<Move>& from_scrambled_scramble) const;

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