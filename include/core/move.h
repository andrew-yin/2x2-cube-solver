#pragma once

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
inline std::string MoveToString(const Move& move) {
  switch (move) {
    case F:
      return "F";
    case Fp:
      return "F'";
    case F2:
      return "F2";
    case B:
      return "B";
    case Bp:
      return "B'";
    case B2:
      return "B2";
    case U:
      return "U";
    case Up:
      return "U'";
    case U2:
      return "U2";
    case D:
      return "D";
    case Dp:
      return "D'";
    case D2:
      return "D2";
    case R:
      return "R";
    case Rp:
      return "R'";
    case R2:
      return "R2";
    case L:
      return "L";
    case Lp:
      return "L'";
    case L2:
      return "L2";
    default:
      return "";
  }
}

}  // namespace cubesolver