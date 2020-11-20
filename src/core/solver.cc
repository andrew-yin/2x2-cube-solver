#include <queue>
#include "core/solver.h"

namespace cubesolver {

std::vector<std::string> Solver::SolveCube(const Cube& scrambled_cube) const {
  std::vector<std::string> scramble;

  std::queue<std::pair<Cube, std::vector<std::string>>> queue;
  queue.push(std::pair<Cube, std::vector<std::string>>(Cube(), std::vector<std::string>()));

  while(!queue.empty()) {
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
             solution.push_back(move.substr(0,1));
           } else if (last_char == '2') {
             solution.push_back(move);
           } else {
             solution.push_back(move + "'");
           }
         }
      } else{
        solution.push_back("Do nothing! It's already solved.");
      }
      return solution;
    }

    if (!IsFrontMove(last_move) || last_move == " ") {
      cube.MoveF();
      scramble.push_back("F");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveFP();
      scramble.pop_back();

      cube.MoveFP();
      scramble.push_back("F'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveF();
      scramble.pop_back();

      cube.MoveF2();
      scramble.push_back("F2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveF2();
      scramble.pop_back();
    }

    if (!IsBackMove(last_move) || last_move == " ") {
      cube.MoveB();
      scramble.push_back("B");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveBP();
      scramble.pop_back();

      cube.MoveBP();
      scramble.push_back("B'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveB();
      scramble.pop_back();

      cube.MoveB2();
      scramble.push_back("B2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveB2();
      scramble.pop_back();
    }

    if (!IsRightMove(last_move) || last_move == " ") {
      cube.MoveR();
      scramble.push_back("R");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveRP();
      scramble.pop_back();

      cube.MoveRP();
      scramble.push_back("R'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveR();
      scramble.pop_back();

      cube.MoveR2();
      scramble.push_back("R2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveR2();
      scramble.pop_back();
    }

    if (!IsLeftMove(last_move) || last_move == " ") {
      cube.MoveL();
      scramble.push_back("L");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveLP();
      scramble.pop_back();

      cube.MoveLP();
      scramble.push_back("L'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveL();
      scramble.pop_back();

      cube.MoveL2();
      scramble.push_back("L2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveL2();
      scramble.pop_back();
    }

    if (!IsUpMove(last_move) || last_move == " ") {
      cube.MoveU();
      scramble.push_back("U");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveUP();
      scramble.pop_back();

      cube.MoveUP();
      scramble.push_back("U'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveU();
      scramble.pop_back();

      cube.MoveU2();
      scramble.push_back("U2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveU2();
      scramble.pop_back();
    }

    if (!IsDownMove(last_move) || last_move == " ") {
      cube.MoveD();
      scramble.push_back("D");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveDP();
      scramble.pop_back();

      cube.MoveDP();
      scramble.push_back("D'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveD();
      scramble.pop_back();

      cube.MoveD2();
      scramble.push_back("D2");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveD2();
      scramble.pop_back();
    }
  }

  return std::vector<std::string>();
}

bool Solver::IsFrontMove(const std::string &move) const {
  return move == "F" || move == "F2" || move == "F'";
}

bool Solver::IsRightMove(const std::string &move) const {
  return move == "R" || move == "R2" || move == "R'";
}

bool Solver::IsLeftMove(const std::string &move) const {
  return move == "L" || move == "L2" || move == "L'";
}

bool Solver::IsUpMove(const std::string &move) const {
  return move == "U" || move == "U2" || move == "U'";
}

bool Solver::IsBackMove(const std::string &move) const {
  return move == "B" || move == "B2" || move == "B'";
}

bool Solver::IsDownMove(const std::string &move) const {
  return move == "D" || move == "D2" || move == "D'";
}

}