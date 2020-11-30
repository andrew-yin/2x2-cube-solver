#include "core/solver.h"

#include <core/corner.h>
#include <core/face.h>

#include <queue>

namespace cubesolver {

std::vector<std::string> Solver::SolveCube(const Cube &scrambled_cube) const {
  std::vector<std::string> scramble;

  std::queue<std::pair<Cube, std::vector<std::string>>> queue;

  Cube start(scrambled_cube.stickers_[front][up_left], scrambled_cube.stickers_[up][low_left],
             scrambled_cube.stickers_[left][up_right]);
  queue.push(std::pair<Cube, std::vector<std::string>>(
      start, std::vector<std::string>()));

  while (!queue.empty()) {
    std::pair<Cube, std::vector<std::string>> cube_and_scramble = queue.front();
    queue.pop();

    Cube cube = cube_and_scramble.first;
    std::vector<std::string> scramble = cube_and_scramble.second;

    std::string last_move = !scramble.empty() ? scramble.back() : " ";

    if (cube == scrambled_cube) {
      std::vector<std::string> solution;
      if (!scramble.empty()) {
        for (auto i = scramble.rbegin(); i != scramble.rend(); i++) {
          std::string move = *i;
          char last_char = move.back();
          if (last_char == '\'') {
            solution.push_back(move.substr(0, 1));
          } else if (last_char == '2') {
            solution.push_back(move);
          } else {
            solution.push_back(move + "'");
          }
        }
      } else {
        solution.push_back("Do nothing! It's already solved.");
      }
      return solution;
    }

    if (!IsBackMove(last_move) || last_move == " ") {
      cube.MoveB();
      scramble.push_back("B");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveB();
      scramble.push_back("B2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveB();
      scramble.push_back("B'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveB();
    }

    if (!IsRightMove(last_move) || last_move == " ") {
      cube.MoveR();
      scramble.push_back("R");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveR();
      scramble.push_back("R2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveR();
      scramble.push_back("R'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveR();
    }

    if (!IsDownMove(last_move) || last_move == " ") {
      cube.MoveD();
      scramble.push_back("D");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveD();
      scramble.push_back("D2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveD();
      scramble.push_back("D'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      scramble.pop_back();

      cube.MoveD();
    }
  }

  return std::vector<std::string>();
}

bool Solver::IsRightMove(const std::string &move) const {
  return move == "R" || move == "R2" || move == "R'";
}

bool Solver::IsBackMove(const std::string &move) const {
  return move == "B" || move == "B2" || move == "B'";
}

bool Solver::IsDownMove(const std::string &move) const {
  return move == "D" || move == "D2" || move == "D'";
}

}  // namespace cubesolver