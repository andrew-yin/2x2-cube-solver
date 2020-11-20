#include <core/solver.h>
#include <iostream>

using namespace cubesolver;

int main() {
  Solver solver;

  /* Scramble: R U2 L' B D */
  Color ful = yellow;
  Color fur = blue;
  Color fdl = white;
  Color fdr = orange;

  Color rul = orange;
  Color rur = blue;
  Color rdl = yellow;
  Color rdr = yellow;

  Color uul = orange;
  Color uur = red;
  Color udl = green;
  Color udr = white;

  Color lul = white;
  Color lur = orange;
  Color ldl = green;
  Color ldr = green;

  Color bul = white;
  Color bur = green;
  Color bdl = red;
  Color bdr = yellow;

  Color dul = red;
  Color dur = blue;
  Color ddl = red;
  Color ddr = blue;

  Cube scrambled(ful,
                 fur,
                 fdl,
                 fdr,
                 bul,
                 bur,
                 bdl,
                 bdr,
                 lur,
                 lul,
                 ldl,
                 ldr,
                 rul,
                 rur,
                 rdl,
                 rdr,
                 uur,
                 uul,
                 udl,
                 udr,
                 dur,
                 dul,
                 ddl,
                 ddr);

  std::cout << "Searching..." << std::endl;

  std::vector<std::string> solution = solver.SolveCube(scrambled);
  std::cout << "Solution: ";
  for (std::string move: solution) {
    std::cout << move << " ";
  }
  
  return 0;
}