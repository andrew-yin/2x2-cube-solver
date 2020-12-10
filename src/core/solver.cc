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

std::vector<Move> Solver::SolveCube(Cube scrambled_cube) const {
  if (IsValidCube(scrambled_cube)) {
    std::queue<std::pair<Cube, std::vector<Move>>> from_solved_queue;
    std::unordered_map<ID, std::vector<Move>> past_from_solved_states;

    Cube solved_cube(scrambled_cube.stickers_[kFront][kUpperLeft],
                     scrambled_cube.stickers_[kUp][kLowerLeft],
                     scrambled_cube.stickers_[kLeft][kUpperRight]);
    from_solved_queue.push(
        std::pair<Cube, std::vector<Move>>(solved_cube, std::vector<Move>()));
    past_from_solved_states[solved_cube.GetID()] = std::vector<Move>();

    std::queue<std::pair<Cube, std::vector<Move>>> from_scrambled_queue;
    std::unordered_map<ID, std::vector<Move>> past_from_scrambled_states;
    from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
        scrambled_cube, std::vector<Move>()));
    past_from_scrambled_states[scrambled_cube.GetID()] = std::vector<Move>();

    while (!from_solved_queue.empty() && !from_scrambled_queue.empty()) {
      std::pair<Cube, std::vector<Move>> from_solved_cube_scramble =
          from_solved_queue.front();
      from_solved_queue.pop();

      Cube from_solved_cube = from_solved_cube_scramble.first;
      std::vector<Move> from_solved_scramble = from_solved_cube_scramble.second;

      std::pair<Cube, std::vector<Move>> from_scrambled_cube_scramble =
          from_scrambled_queue.front();
      from_scrambled_queue.pop();

      Cube from_scrambled_cube = from_scrambled_cube_scramble.first;
      std::vector<Move> from_scrambled_scramble =
          from_scrambled_cube_scramble.second;

      auto searched_from_scrambled_cube =
          past_from_scrambled_states.find(from_solved_cube.GetID());
      if (searched_from_scrambled_cube != past_from_scrambled_states.end()) {
        std::vector<Move> solution;

        for (const Move& move : searched_from_scrambled_cube->second) {
          solution.push_back(move);
        }
        for (auto move = from_solved_scramble.rbegin();
             move != from_solved_scramble.rend(); move++) {
          solution.push_back(*move);
        }
        return solution;
      }

      auto searched_from_solved_cube =
          past_from_solved_states.find(from_scrambled_cube.GetID());
      if (searched_from_solved_cube != past_from_solved_states.end()) {
        std::vector<Move> solution;

        for (const Move& move : from_scrambled_scramble) {
          solution.push_back(move);
        }
        for (auto move = searched_from_solved_cube->second.rbegin();
             move != searched_from_solved_cube->second.rend(); move++) {
          solution.push_back(*move);
        }
        return solution;
      }

      /* We only consider back, right, and down move since otherwise we would
       * break the fixed orientation set by the corner.
       *
       * Side note: We add the opposite of the move to the scramble vector since
       * we are traversing backwards from a solved solution. This simply makes
       * outputting a solution easier */
      Move from_solved_last_move =
          !from_solved_scramble.empty() ? from_solved_scramble.back() : kNoMove;
      if (!IsBackMove(from_solved_last_move) ||
          from_solved_last_move == kNoMove) {
        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kBPrime);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kB2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kB);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
      }

      if (!IsRightMove(from_solved_last_move) ||
          from_solved_last_move == kNoMove) {
        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kRPrime);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kR2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kR);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
      }

      if (!IsDownMove(from_solved_last_move) ||
          from_solved_last_move == kNoMove) {
        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kDPrime);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kD2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(kD);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveD();
      }

      Move from_scrambled_last_move = !from_scrambled_scramble.empty()
                                          ? from_scrambled_scramble.back()
                                          : kNoMove;
      if (!IsBackMove(from_scrambled_last_move) ||
          from_scrambled_last_move == kNoMove) {
        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kB);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kB2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kBPrime);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
      }

      if (!IsRightMove(from_scrambled_last_move) ||
          from_scrambled_last_move == kNoMove) {
        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kR);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kR2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kRPrime);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
      }

      if (!IsDownMove(from_scrambled_last_move) ||
          from_scrambled_last_move == kNoMove) {
        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kD);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kD2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(kDPrime);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
      }
    }
  } else {
    return std::vector<Move>({kNoMove});
  }
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