#include "core/cube.h"

#include <core/corner.h>
#include <core/face.h>

namespace cubesolver {

Cube::Cube() {
  for (size_t i = 0; i < kNumCornersPerFace; i++) {
    stickers_[front][i] = green;
    stickers_[back][i] = blue;
    stickers_[up][i] = white;
    stickers_[down][i] = yellow;
    stickers_[left][i] = orange;
    stickers_[right][i] = red;
  }
}

Cube::Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
               stickers)
    : stickers_(stickers) {
}

void Cube::MoveU() {
  Color uur_org = stickers_[up][up_right];
  Color uul_org = stickers_[up][up_left];
  Color udr_org = stickers_[up][low_right];
  Color udl_org = stickers_[up][low_left];

  stickers_[up][up_right] = uul_org;
  stickers_[up][up_left] = udl_org;
  stickers_[up][low_left] = udr_org;
  stickers_[up][low_right] = uur_org;

  Color fur_org = stickers_[front][up_right];
  Color ful_org = stickers_[front][up_left];
  Color lul_org = stickers_[left][up_left];
  Color lur_org = stickers_[left][up_right];
  Color rul_org = stickers_[right][up_left];
  Color rur_org = stickers_[right][up_right];
  Color bur_org = stickers_[back][up_right];
  Color bul_org = stickers_[back][up_left];

  stickers_[front][up_left] = rul_org;
  stickers_[front][up_right] = rur_org;
  stickers_[left][up_right] = fur_org;
  stickers_[left][up_left] = ful_org;
  stickers_[right][up_left] = bul_org;
  stickers_[right][up_right] = bur_org;
  stickers_[back][up_left] = lul_org;
  stickers_[back][up_right] = lur_org;
}

void Cube::MoveD() {
  Color dur_org = stickers_[down][up_right];
  Color dul_org = stickers_[down][up_left];
  Color ddr_org = stickers_[down][low_right];
  Color ddl_org = stickers_[down][low_left];

  stickers_[down][up_right] = dul_org;
  stickers_[down][up_left] = ddl_org;
  stickers_[down][low_left] = ddr_org;
  stickers_[down][low_right] = dur_org;

  Color fdr_org = stickers_[front][low_right];
  Color fdl_org = stickers_[front][low_left];
  Color ldl_org = stickers_[left][low_left];
  Color ldr_org = stickers_[left][low_right];
  Color rdl_org = stickers_[right][low_left];
  Color rdr_org = stickers_[right][low_right];
  Color bdr_org = stickers_[back][low_right];
  Color bdl_org = stickers_[back][low_left];

  stickers_[front][low_left] = ldl_org;
  stickers_[front][low_right] = ldr_org;
  stickers_[left][low_right] = bdr_org;
  stickers_[left][low_left] = bdl_org;
  stickers_[right][low_left] = fdl_org;
  stickers_[right][low_right] = fdr_org;
  stickers_[back][low_left] = rdl_org;
  stickers_[back][low_right] = rdr_org;
}

void Cube::MoveL() {
  Color lur_org = stickers_[left][up_right];
  Color lul_org = stickers_[left][up_left];
  Color ldr_org = stickers_[left][low_right];
  Color ldl_org = stickers_[left][low_left];

  stickers_[left][up_right] = lul_org;
  stickers_[left][up_left] = ldl_org;
  stickers_[left][low_left] = ldr_org;
  stickers_[left][low_right] = lur_org;

  Color uul_org = stickers_[up][up_left];
  Color udl_org = stickers_[up][low_left];
  Color ful_org = stickers_[front][up_left];
  Color fdl_org = stickers_[front][low_left];
  Color bur_org = stickers_[back][up_right];
  Color bdr_org = stickers_[back][low_right];
  Color dul_org = stickers_[down][up_left];
  Color ddl_org = stickers_[down][low_left];

  stickers_[front][up_left] = uul_org;
  stickers_[front][low_left] = udl_org;
  stickers_[up][up_left] = bdr_org;
  stickers_[up][low_left] = bur_org;
  stickers_[down][up_left] = ful_org;
  stickers_[down][low_left] = fdl_org;
  stickers_[back][up_right] = ddl_org;
  stickers_[back][low_right] = dul_org;
}

void Cube::MoveR() {
  Color rur_org = stickers_[right][up_right];
  Color rul_org = stickers_[right][up_left];
  Color rdr_org = stickers_[right][low_right];
  Color rdl_org = stickers_[right][low_left];

  stickers_[right][up_right] = rul_org;
  stickers_[right][up_left] = rdl_org;
  stickers_[right][low_left] = rdr_org;
  stickers_[right][low_right] = rur_org;

  Color uur_org = stickers_[up][up_right];
  Color udr_org = stickers_[up][low_right];
  Color fur_org = stickers_[front][up_right];
  Color fdr_org = stickers_[front][low_right];
  Color bul_org = stickers_[back][up_left];
  Color bdl_org = stickers_[back][low_left];
  Color dur_org = stickers_[down][up_right];
  Color ddr_org = stickers_[down][low_right];

  stickers_[front][up_right] = dur_org;
  stickers_[front][low_right] = ddr_org;
  stickers_[up][up_right] = fur_org;
  stickers_[up][low_right] = fdr_org;
  stickers_[down][up_right] = bdl_org;
  stickers_[down][low_right] = bul_org;
  stickers_[back][up_left] = udr_org;
  stickers_[back][low_left] = uur_org;
}

void Cube::MoveB() {
  Color bur_org = stickers_[back][up_right];
  Color bul_org = stickers_[back][up_left];
  Color bdr_org = stickers_[back][low_right];
  Color bdl_org = stickers_[back][low_left];

  stickers_[back][up_right] = bul_org;
  stickers_[back][up_left] = bdl_org;
  stickers_[back][low_left] = bdr_org;
  stickers_[back][low_right] = bur_org;

  Color uur_org = stickers_[up][up_right];
  Color uul_org = stickers_[up][up_left];
  Color rur_org = stickers_[right][up_right];
  Color rdr_org = stickers_[right][low_right];
  Color lul_org = stickers_[left][up_left];
  Color ldl_org = stickers_[left][low_left];
  Color ddr_org = stickers_[down][low_right];
  Color ddl_org = stickers_[down][low_left];

  stickers_[up][up_left] = rur_org;
  stickers_[up][up_right] = rdr_org;
  stickers_[right][up_right] = ddr_org;
  stickers_[right][low_right] = ddl_org;
  stickers_[left][up_left] = uur_org;
  stickers_[left][low_left] = uul_org;
  stickers_[down][low_left] = lul_org;
  stickers_[down][low_right] = ldl_org;
}

void Cube::MoveF() {
  Color ful_org = stickers_[front][up_left];
  Color fur_org = stickers_[front][up_right];
  Color fdl_org = stickers_[front][low_left];
  Color fdr_org = stickers_[front][low_right];

  stickers_[front][up_left] = fdl_org;
  stickers_[front][up_right] = ful_org;
  stickers_[front][low_left] = fdr_org;
  stickers_[front][low_right] = fur_org;

  Color udl_org = stickers_[up][low_left];
  Color udr_org = stickers_[up][low_right];
  Color rul_org = stickers_[right][up_left];
  Color rdl_org = stickers_[right][low_left];
  Color lur_org = stickers_[left][up_right];
  Color ldr_org = stickers_[left][low_right];
  Color dul_org = stickers_[down][up_left];
  Color dur_org = stickers_[down][up_right];

  stickers_[up][low_left] = ldr_org;
  stickers_[up][low_right] = lur_org;
  stickers_[right][up_left] = udl_org;
  stickers_[right][low_left] = udr_org;
  stickers_[left][up_right] = dul_org;
  stickers_[left][low_right] = dur_org;
  stickers_[down][up_left] = rdl_org;
  stickers_[down][up_right] = rul_org;
}

bool Cube::operator==(const Cube& b) const {
  return (stickers_[front][up_left] == b.stickers_[front][up_left]) &&
         (stickers_[front][up_right] == b.stickers_[front][up_right]) &&
         (stickers_[front][low_left] == b.stickers_[front][low_left]) &&
         (stickers_[front][low_right] == b.stickers_[front][low_right]) &&
         (stickers_[left][up_left] == b.stickers_[left][up_left]) &&
         (stickers_[left][up_right] == b.stickers_[left][up_right]) &&
         (stickers_[left][low_left] == b.stickers_[left][low_left]) &&
         (stickers_[left][low_right] == b.stickers_[left][low_right]) &&
         (stickers_[up][up_left] == b.stickers_[up][up_left]) &&
         (stickers_[up][up_right] == b.stickers_[up][up_right]) &&
         (stickers_[up][low_left] == b.stickers_[up][low_left]) &&
         (stickers_[up][low_right] == b.stickers_[up][low_right]) &&
         (stickers_[right][up_left] == b.stickers_[right][up_left]) &&
         (stickers_[right][up_right] == b.stickers_[right][up_right]) &&
         (stickers_[right][low_left] == b.stickers_[right][low_left]) &&
         (stickers_[right][low_right] == b.stickers_[right][low_right]) &&
         (stickers_[down][up_left] == b.stickers_[down][up_left]) &&
         (stickers_[down][up_right] == b.stickers_[down][up_right]) &&
         (stickers_[down][low_left] == b.stickers_[down][low_left]) &&
         (stickers_[down][low_right] == b.stickers_[down][low_right]) &&
         (stickers_[back][up_left] == b.stickers_[back][up_left]) &&
         (stickers_[back][up_right] == b.stickers_[back][up_right]) &&
         (stickers_[back][low_left] == b.stickers_[back][low_left]) &&
         (stickers_[back][low_right] == b.stickers_[back][low_right]);
}

}  // namespace cubesolver