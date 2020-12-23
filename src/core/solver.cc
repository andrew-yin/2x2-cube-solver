#include "core/solver.h"

#include <iostream>
#include <queue>
#include <unordered_map>

namespace cubesolver {

std::string MoveToString(const Move& move) {
  switch (move) {
    case kF:
      return "F";
    case kFPrime:
      return "F'";
    case kF2:
      return "F2";
    case kB:
      return "B";
    case kBPrime:
      return "B'";
    case kB2:
      return "B2";
    case kU:
      return "U";
    case kUPrime:
      return "U'";
    case kU2:
      return "U2";
    case kD:
      return "D";
    case kDPrime:
      return "D'";
    case kD2:
      return "D2";
    case kR:
      return "R";
    case kRPrime:
      return "R'";
    case kR2:
      return "R2";
    case kL:
      return "L";
    case kLPrime:
      return "L'";
    case kL2:
      return "L2";
    case kNoMove:
      return "Error: No solution exists for the given scramble.";
  }
}

std::vector<Move> Solver::SolveCube(Cube scrambled_cube) {
  if (IsValidCube(scrambled_cube)) {
    Reset();
    Initialize(scrambled_cube);

    while (!from_solved_queue_.empty() && !from_scrambled_queue_.empty()) {
      /* Pull information of the cube state and scramble from the front
       * of both queues */
      std::pair<Cube, std::vector<Move>> from_solved_cube_scramble =
          from_solved_queue_.front();
      from_solved_queue_.pop();

      std::pair<Cube, std::vector<Move>> from_scrambled_cube_scramble =
          from_scrambled_queue_.front();
      from_scrambled_queue_.pop();

      Cube from_solved_cube = from_solved_cube_scramble.first;
      std::vector<Move> from_solved_scramble = from_solved_cube_scramble.second;
      Cube from_scrambled_cube = from_scrambled_cube_scramble.first;
      std::vector<Move> from_scrambled_scramble =
          from_scrambled_cube_scramble.second;

      /* Check if we have a solution */
      auto searched_from_scrambled_cube =
          past_from_scrambled_states_.find(from_solved_cube.GetID());
      if (searched_from_scrambled_cube != past_from_scrambled_states_.end()) {
        return GetSolution(from_solved_scramble,
                           searched_from_scrambled_cube->second);
      }
      auto searched_from_solved_cube =
          past_from_solved_states_.find(from_scrambled_cube.GetID());
      if (searched_from_solved_cube != past_from_solved_states_.end()) {
        return GetSolution(searched_from_solved_cube->second,
                           from_scrambled_scramble);
      }

      /* We only consider back, right, and down move since otherwise we would
         break the fixed orientation set by the corner */
      Move from_solved_last_move =
          !from_solved_scramble.empty() ? from_solved_scramble.back() : kNoMove;
      Move from_scrambled_last_move = !from_scrambled_scramble.empty()
                                          ? from_scrambled_scramble.back()
                                          : kNoMove;
      GenerateBackNodes(from_solved_cube, from_solved_scramble,
                        from_solved_last_move, from_scrambled_cube,
                        from_scrambled_scramble, from_scrambled_last_move);
      GenerateRightNodes(from_solved_cube, from_scrambled_cube,
                         from_solved_scramble, from_scrambled_scramble,
                         from_solved_last_move, from_scrambled_last_move);
      GenerateDownNodes(from_solved_cube, from_scrambled_cube,
                        from_solved_scramble, from_scrambled_scramble,
                        from_solved_last_move, from_scrambled_last_move);
    }
  } else {
    return std::vector<Move>({kNoMove});
  }

  return std::vector<Move>({kNoMove});
}

void Solver::Reset() {
  past_from_solved_states_.clear();
  past_from_scrambled_states_.clear();

  /**
   * Code for how to clear a STL queue derived from:
   *
   * https://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently
   */
  std::queue<std::pair<Cube, std::vector<Move>>> empty1;
  std::swap(from_solved_queue_, empty1);
  std::queue<std::pair<Cube, std::vector<Move>>> empty2;
  std::swap(from_solved_queue_, empty2);
}

void Solver::Initialize(const Cube& scrambled_cube) {
  Cube solved_cube(scrambled_cube.stickers_[kFront][kUpperLeft],
                   scrambled_cube.stickers_[kUp][kLowerLeft],
                   scrambled_cube.stickers_[kLeft][kUpperRight]);

  from_solved_queue_.push(
      std::pair<Cube, std::vector<Move>>(solved_cube, std::vector<Move>()));
  past_from_solved_states_[solved_cube.GetID()] = std::vector<Move>();

  from_scrambled_queue_.push(
      std::pair<Cube, std::vector<Move>>(scrambled_cube, std::vector<Move>()));
  past_from_scrambled_states_[scrambled_cube.GetID()] = std::vector<Move>();
}

void Solver::GenerateBackNodes(Cube& from_solved_cube,
                               std::vector<Move>& from_solved_scramble,
                               const Move& from_solved_last_move,
                               Cube& from_scrambled_cube,
                               std::vector<Move>& from_scrambled_scramble,
                               const Move& from_scrambled_last_move) {
  if (!IsBackMove(from_solved_last_move) || from_solved_last_move == kNoMove) {
    from_solved_cube.MoveB();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kBPrime);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveB();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kB2);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveB();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kB);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveB();
  }
  if (!IsBackMove(from_scrambled_last_move) ||
      from_scrambled_last_move == kNoMove) {
    from_scrambled_cube.MoveB();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kB);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveB();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kB2);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveB();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kBPrime);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveB();
  }
}

void Solver::GenerateRightNodes(Cube& from_solved_cube,
                                Cube& from_scrambled_cube,
                                std::vector<Move>& from_solved_scramble,
                                std::vector<Move>& from_scrambled_scramble,
                                const Move& from_solved_last_move,
                                const Move& from_scrambled_last_move) {
  if (!IsRightMove(from_solved_last_move) || from_solved_last_move == kNoMove) {
    from_solved_cube.MoveR();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kRPrime);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveR();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kR2);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveR();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kR);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveR();
  }

  if (!IsRightMove(from_scrambled_last_move) ||
      from_scrambled_last_move == kNoMove) {
    from_scrambled_cube.MoveR();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kR);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveR();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kR2);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveR();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kRPrime);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveR();
  }
}

void Solver::GenerateDownNodes(Cube& from_solved_cube,
                               Cube& from_scrambled_cube,
                               std::vector<Move>& from_solved_scramble,
                               std::vector<Move>& from_scrambled_scramble,
                               const Move& from_solved_last_move,
                               const Move& from_scrambled_last_move) {
  if (!IsDownMove(from_solved_last_move) || from_solved_last_move == kNoMove) {
    from_solved_cube.MoveD();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kDPrime);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveD();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kD2);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveD();
    if (past_from_solved_states_.count(from_solved_cube.GetID()) == 0) {
      from_solved_scramble.push_back(kD);
      from_solved_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_solved_cube, from_solved_scramble));
      past_from_solved_states_[from_solved_cube.GetID()] = from_solved_scramble;
      from_solved_scramble.pop_back();
    }

    from_solved_cube.MoveD();
  }

  if (!IsDownMove(from_scrambled_last_move) ||
      from_scrambled_last_move == kNoMove) {
    from_scrambled_cube.MoveD();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kD);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveD();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kD2);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveD();
    if (past_from_scrambled_states_.count(from_scrambled_cube.GetID()) == 0) {
      from_scrambled_scramble.push_back(kDPrime);
      from_scrambled_queue_.push(std::pair<Cube, std::vector<Move>>(
          from_scrambled_cube, from_scrambled_scramble));
      from_scrambled_scramble.pop_back();
    }

    from_scrambled_cube.MoveD();
  }
}

std::vector<Move> Solver::GetSolution(
    std::vector<Move> from_solved_scramble,
    const std::vector<Move>& from_scrambled_scramble) const {
  std::vector<Move> solution;
  for (const Move& move : from_scrambled_scramble) {
    solution.push_back(move);
  }
  for (auto move = from_solved_scramble.rbegin();
       move != from_solved_scramble.rend(); move++) {
    solution.push_back(*move);
  }
  return solution;
}

bool Solver::IsBackMove(const Move& move) const {
  return move == kB || move == kBPrime || move == kB2;
}

bool Solver::IsRightMove(const Move& move) const {
  return move == kR || move == kRPrime || move == kR2;
}

bool Solver::IsDownMove(const Move& move) const {
  return move == kD || move == kDPrime || move == kD2;
}

bool Solver::IsValidCube(const Cube& cube) const {
  return IsValidCorner(cube.stickers_[kFront][kUpperLeft],
                       cube.stickers_[kUp][kLowerLeft],
                       cube.stickers_[kLeft][kUpperRight]) &&
         IsValidCorner(cube.stickers_[kFront][kUpperRight],
                       cube.stickers_[kUp][kLowerRight],
                       cube.stickers_[kRight][kUpperLeft]) &&
         IsValidCorner(cube.stickers_[kFront][kLowerLeft],
                       cube.stickers_[kLeft][kLowerRight],
                       cube.stickers_[kDown][kUpperLeft]) &&
         IsValidCorner(cube.stickers_[kFront][kLowerRight],
                       cube.stickers_[kDown][kUpperRight],
                       cube.stickers_[kRight][kLowerLeft]) &&
         IsValidCorner(cube.stickers_[kBack][kUpperLeft],
                       cube.stickers_[kUp][kUpperRight],
                       cube.stickers_[kRight][kUpperRight]) &&
         IsValidCorner(cube.stickers_[kBack][kUpperRight],
                       cube.stickers_[kUp][kUpperLeft],
                       cube.stickers_[kLeft][kUpperLeft]) &&
         IsValidCorner(cube.stickers_[kBack][kLowerLeft],
                       cube.stickers_[kDown][kLowerRight],
                       cube.stickers_[kRight][kLowerRight]) &&
         IsValidCorner(cube.stickers_[kBack][kLowerRight],
                       cube.stickers_[kDown][kLowerLeft],
                       cube.stickers_[kLeft][kLowerLeft]);
}

bool Solver::IsValidCorner(const Color& color1, const Color& color2,
                           const Color& color3) const {
  return (color1 != color2 && color1 != color3 && color2 != color3) &&
         (color1 != GetOppositeSide(color2) &&
          color1 != GetOppositeSide(color3) &&
          color2 != GetOppositeSide(color3));
}

}  // namespace cubesolver