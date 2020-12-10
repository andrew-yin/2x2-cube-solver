#include "core/solver.h"

#include <iostream>
#include <queue>
#include <unordered_map>

namespace cubesolver {

std::string MoveToString(const Move& move) {
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
    case no_move:
      return "Error: No solution exists for the given scramble.";
  }
}

std::vector<Move> Solver::SolveCube(Cube scrambled_cube) const {
  if (IsValidCube(scrambled_cube)) {
    std::queue<std::pair<Cube, std::vector<Move>>> from_solved_queue;
    std::unordered_map<ID, std::vector<Move>> past_from_solved_states;

    Cube solved_cube(scrambled_cube.stickers_[front][up_left],
                     scrambled_cube.stickers_[up][low_left],
                     scrambled_cube.stickers_[left][up_right]);
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
          !from_solved_scramble.empty() ? from_solved_scramble.back() : no_move;
      if (!IsBackMove(from_solved_last_move) ||
          from_solved_last_move == no_move) {
        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(Bp);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(B2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(B);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveB();
      }

      if (!IsRightMove(from_solved_last_move) ||
          from_solved_last_move == no_move) {
        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(Rp);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(R2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(R);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveR();
      }

      if (!IsDownMove(from_solved_last_move) ||
          from_solved_last_move == no_move) {
        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(Dp);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(D2);
          from_solved_queue.push(std::pair<Cube, std::vector<Move>>(
              from_solved_cube, from_solved_scramble));
          past_from_solved_states[from_solved_cube.GetID()] =
              from_solved_scramble;
          from_solved_scramble.pop_back();
        }

        from_solved_cube.MoveD();
        if (past_from_solved_states.count(from_solved_cube.GetID()) == 0) {
          from_solved_scramble.push_back(D);
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
                                          : no_move;
      if (!IsBackMove(from_scrambled_last_move) ||
          from_scrambled_last_move == no_move) {
        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(B);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(B2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(Bp);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveB();
      }

      if (!IsRightMove(from_scrambled_last_move) ||
          from_scrambled_last_move == no_move) {
        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(R);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(R2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(Rp);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveR();
      }

      if (!IsDownMove(from_scrambled_last_move) ||
          from_scrambled_last_move == no_move) {
        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(D);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(D2);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
        if (past_from_scrambled_states.count(from_scrambled_cube.GetID()) ==
            0) {
          from_scrambled_scramble.push_back(Dp);
          from_scrambled_queue.push(std::pair<Cube, std::vector<Move>>(
              from_scrambled_cube, from_scrambled_scramble));
          from_scrambled_scramble.pop_back();
        }

        from_scrambled_cube.MoveD();
      }
    }
  } else {
    return std::vector<Move>({no_move});
  }
}

bool Solver::IsBackMove(const Move& move) const {
  return move == B || move == Bp || move == B2;
}

bool Solver::IsRightMove(const Move& move) const {
  return move == R || move == Rp || move == R2;
}

bool Solver::IsDownMove(const Move& move) const {
  return move == D || move == Dp || move == D2;
}

bool Solver::IsValidCube(const Cube& cube) const {
  return IsValidCorner(cube.stickers_[front][up_left],
                       cube.stickers_[up][low_left],
                       cube.stickers_[left][up_right]) &&
         IsValidCorner(cube.stickers_[front][up_right],
                       cube.stickers_[up][low_right],
                       cube.stickers_[right][up_left]) &&
         IsValidCorner(cube.stickers_[front][low_left],
                       cube.stickers_[left][low_right],
                       cube.stickers_[down][up_left]) &&
         IsValidCorner(cube.stickers_[front][low_right],
                       cube.stickers_[down][up_right],
                       cube.stickers_[right][low_left]) &&
         IsValidCorner(cube.stickers_[back][up_left],
                       cube.stickers_[up][up_right],
                       cube.stickers_[right][up_right]) &&
         IsValidCorner(cube.stickers_[back][up_right],
                       cube.stickers_[up][up_left],
                       cube.stickers_[left][up_left]) &&
         IsValidCorner(cube.stickers_[back][low_left],
                       cube.stickers_[down][low_right],
                       cube.stickers_[right][low_right]) &&
         IsValidCorner(cube.stickers_[back][low_right],
                       cube.stickers_[down][low_left],
                       cube.stickers_[left][low_left]);
}

bool Solver::IsValidCorner(const Color& color1, const Color& color2,
                           const Color& color3) const {
  return (color1 != color2 && color1 != color3 && color2 != color3) &&
         (color1 != GetOppositeSide(color2) &&
          color1 != GetOppositeSide(color3) &&
          color2 != GetOppositeSide(color3));
}

}  // namespace cubesolver