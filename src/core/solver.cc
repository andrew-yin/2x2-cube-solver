#include <queue>
#include <iostream>
#include "core/solver.h"

namespace cubesolver {

std::vector<std::string> Solver::SolveCube(const Cube& scrambled_cube) {
  std::vector<std::string> scramble;

  std::queue<std::pair<Cube, std::vector<std::string>>> queue;
  queue.push(std::pair<Cube, std::vector<std::string>>(Cube(), std::vector<std::string>()));

  size_t count = 0;
  while(!queue.empty()) {
    count++;
    std::pair<Cube, std::vector<std::string>> cube_and_scramble = queue.front();
    queue.pop();

    Cube cube = cube_and_scramble.first;
    std::vector<std::string> scramble = cube_and_scramble.second;

    std::string last_move = !scramble.empty() ? scramble.back() : " ";

    std::cout << "searched: " << count << std::endl;

    if (cube == scrambled_cube) {
      std::vector<std::string> solution;
      if (last_move != " ") {
         for (auto i = scramble.rbegin(); i != scramble.rend(); i++) {
           std::string move = *i;
           if (move.size() == 2) {
             solution.push_back(move.substr(0,1));
           } else {
             solution.push_back(move + "'");
           }
         }
      }
      return solution;
    }

    if (last_move != "F'") {
      cube.MoveF();
      scramble.push_back("F");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveFP();
      scramble.pop_back();
    }

    if (last_move != "F") {
      cube.MoveFP();
      scramble.push_back("F'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveF();
      scramble.pop_back();
    }

    if (last_move != "B'") {
      cube.MoveB();
      scramble.push_back("B");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveBP();
      scramble.pop_back();
    }

    if (last_move != "B") {
      cube.MoveBP();
      scramble.push_back("B'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveB();
      scramble.pop_back();
    }

    if (last_move != "R'") {
      cube.MoveR();
      scramble.push_back("R");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveRP();
      scramble.pop_back();
    }

    if (last_move != "R") {
      cube.MoveRP();
      scramble.push_back("R'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveR();
      scramble.pop_back();
    }

    if (last_move != "L'") {
      cube.MoveL();
      scramble.push_back("L");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveLP();
      scramble.pop_back();
    }

    if (last_move != "L") {
      cube.MoveLP();
      scramble.push_back("L'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveL();
      scramble.pop_back();
    }

    if (last_move != "U'") {
      cube.MoveU();
      scramble.push_back("U");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveUP();
      scramble.pop_back();
    }

    if (last_move != "U") {
      cube.MoveUP();
      scramble.push_back("U'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveU();
      scramble.pop_back();
    }

    if (last_move != "D'") {
      cube.MoveD();
      scramble.push_back("D");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveDP();
      scramble.pop_back();
    }

    if (last_move != "D") {
      cube.MoveDP();
      scramble.push_back("D'");
      queue.push(std::pair<Cube, std::vector<std::string>>(cube, scramble));
      cube.MoveD();
      scramble.pop_back();
    }
  }

  return std::vector<std::string>();
}

}