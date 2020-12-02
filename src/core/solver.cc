#include "core/solver.h"

#include <core/corner.h>
#include <core/face.h>

#include <iostream>
#include <queue>

namespace cubesolver {

std::vector<Move> Solver::SolveCube(const Cube& scrambled_cube) const {
  std::queue<std::pair<Cube, std::vector<Move>>> ful_queue;
  std::queue<std::pair<Cube, std::vector<Move>>> bdr_queue;

  Cube ful_start(scrambled_cube.stickers_[front][up_left],
                 scrambled_cube.stickers_[up][low_left],
                 scrambled_cube.stickers_[left][up_right], true);
  ful_queue.push(
      std::pair<Cube, std::vector<Move>>(ful_start, std::vector<Move>()));

  Cube bdr_start(scrambled_cube.stickers_[back][low_left],
                 scrambled_cube.stickers_[down][low_right],
                 scrambled_cube.stickers_[right][low_right], false);
  bdr_queue.push(
      std::pair<Cube, std::vector<Move>>(bdr_start, std::vector<Move>()));

  while (!ful_queue.empty() && !bdr_queue.empty()) {
    std::pair<Cube, std::vector<Move>> ful_cube_scramble = ful_queue.front();
    ful_queue.pop();

    Cube ful_cube = ful_cube_scramble.first;
    std::vector<Move> ful_scramble = ful_cube_scramble.second;

    std::pair<Cube, std::vector<Move>> bdr_cube_scramble = bdr_queue.front();
    bdr_queue.pop();

    Cube bdr_cube = bdr_cube_scramble.first;
    std::vector<Move> bdr_scramble = bdr_cube_scramble.second;

    if (ful_cube == scrambled_cube) {
      std::vector<Move> solution;
      for (auto i = ful_scramble.rbegin(); i != ful_scramble.rend(); i++) {
        solution.push_back(*i);
      }
      return solution;
    } else if (bdr_cube == scrambled_cube) {
      std::vector<Move> solution;
      for (auto i = bdr_scramble.rbegin(); i != bdr_scramble.rend(); i++) {
        solution.push_back(*i);
      }
      return solution;
    }

    Move ful_last_move = !ful_scramble.empty() ? ful_scramble.back() : no_move;
    if (!IsBackMove(ful_last_move) || ful_last_move == no_move) {
      ful_cube.MoveB();
      ful_scramble.push_back(Bp);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveB();
      ful_scramble.push_back(B2);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveB();
      ful_scramble.push_back(B);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveB();
    }

    if (!IsRightMove(ful_last_move) || ful_last_move == no_move) {
      ful_cube.MoveR();
      ful_scramble.push_back(Rp);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveR();
      ful_scramble.push_back(R2);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveR();
      ful_scramble.push_back(R);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveR();
    }

    if (!IsDownMove(ful_last_move) || ful_last_move == no_move) {
      ful_cube.MoveD();
      ful_scramble.push_back(Dp);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveD();
      ful_scramble.push_back(D2);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveD();
      ful_scramble.push_back(D);
      ful_queue.push(
          std::pair<Cube, std::vector<Move>>(ful_cube, ful_scramble));
      ful_scramble.pop_back();

      ful_cube.MoveD();
    }

    Move bdr_last_move = !bdr_scramble.empty() ? bdr_scramble.back() : no_move;
    if (!IsUpMove(bdr_last_move) || bdr_last_move == no_move) {
      bdr_cube.MoveU();
      bdr_scramble.push_back(Up);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveU();
      bdr_scramble.push_back(U2);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveU();
      bdr_scramble.push_back(U);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveU();
    }

    if (IsFrontMove(bdr_last_move) || bdr_last_move == no_move) {
      bdr_cube.MoveF();
      bdr_scramble.push_back(Fp);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveF();
      bdr_scramble.push_back(F2);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveF();
      bdr_scramble.push_back(F);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveF();
    }

    if (!IsLeftMove(bdr_last_move) || bdr_last_move == no_move) {
      bdr_cube.MoveL();
      bdr_scramble.push_back(Lp);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveL();
      bdr_scramble.push_back(L2);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveL();
      bdr_scramble.push_back(L);
      bdr_queue.push(
          std::pair<Cube, std::vector<Move>>(bdr_cube, bdr_scramble));
      bdr_scramble.pop_back();

      bdr_cube.MoveL();
    }
  }
  return std::vector<Move>();
}

bool Solver::IsFrontMove(const Move& move) const {
  return move == F || move == Fp || move == F2;
}

bool Solver::IsRightMove(const Move& move) const {
  return move == R || move == Rp || move == R2;
}

bool Solver::IsLeftMove(const Move& move) const {
  return move == L || move == Lp || move == L2;
}

bool Solver::IsUpMove(const Move& move) const {
  return move == U || move == Up || move == U2;
}

bool Solver::IsBackMove(const Move& move) const {
  return move == B || move == Bp || move == B2;
}

bool Solver::IsDownMove(const Move& move) const {
  return move == D || move == Dp || move == D2;
}

}  // namespace cubesolver