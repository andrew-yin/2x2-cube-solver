#include "core/cube.h"

namespace cubesolver {

char ColorToChar(const Color& color) {
  switch (color) {
    case white:
      return 'w';
    case yellow:
      return 'y';
    case red:
      return 'r';
    case orange:
      return 'o';
    case blue:
      return 'b';
    case green:
      return 'g';
  }
}

Color GetOppositeSide(const Color& color) {
  switch (color) {
    case white:
      return yellow;
    case yellow:
      return white;
    case red:
      return orange;
    case orange:
      return red;
    case blue:
      return green;
    case green:
      return blue;
  }
}

Cube::Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
               stickers)
    : stickers_(stickers) {
}

Cube::Cube(const Color& f_color, const Color& u_color, const Color& l_color) {
  Color b_col = GetOppositeSide(f_color);
  Color d_col = GetOppositeSide(u_color);
  Color r_col = GetOppositeSide(l_color);
  for (size_t i = 0; i < kNumCornersPerFace; i++) {
    stickers_[up][i] = u_color;
    stickers_[down][i] = d_col;
    stickers_[left][i] = l_color;
    stickers_[right][i] = r_col;
    stickers_[front][i] = f_color;
    stickers_[back][i] = b_col;
  }
}

void Cube::MoveD() {
  Color dur_org = stickers_[down][up_right];
  Color dul_org = stickers_[down][up_left];
  Color dlr_org = stickers_[down][low_right];
  Color dll_org = stickers_[down][low_left];

  stickers_[down][up_right] = dul_org;
  stickers_[down][up_left] = dll_org;
  stickers_[down][low_left] = dlr_org;
  stickers_[down][low_right] = dur_org;

  Color flr_org = stickers_[front][low_right];
  Color fll_org = stickers_[front][low_left];
  Color lll_org = stickers_[left][low_left];
  Color llr_org = stickers_[left][low_right];
  Color rll_org = stickers_[right][low_left];
  Color rlr_org = stickers_[right][low_right];
  Color blr_org = stickers_[back][low_right];
  Color bll_org = stickers_[back][low_left];

  stickers_[front][low_left] = lll_org;
  stickers_[front][low_right] = llr_org;
  stickers_[left][low_right] = blr_org;
  stickers_[left][low_left] = bll_org;
  stickers_[right][low_left] = fll_org;
  stickers_[right][low_right] = flr_org;
  stickers_[back][low_left] = rll_org;
  stickers_[back][low_right] = rlr_org;
}

void Cube::MoveR() {
  Color rur_org = stickers_[right][up_right];
  Color rul_org = stickers_[right][up_left];
  Color rlr_org = stickers_[right][low_right];
  Color rll_org = stickers_[right][low_left];

  stickers_[right][up_right] = rul_org;
  stickers_[right][up_left] = rll_org;
  stickers_[right][low_left] = rlr_org;
  stickers_[right][low_right] = rur_org;

  Color uur_org = stickers_[up][up_right];
  Color ulr_org = stickers_[up][low_right];
  Color fur_org = stickers_[front][up_right];
  Color flr_org = stickers_[front][low_right];
  Color bul_org = stickers_[back][up_left];
  Color bll_org = stickers_[back][low_left];
  Color dur_org = stickers_[down][up_right];
  Color dlr_org = stickers_[down][low_right];

  stickers_[front][up_right] = dur_org;
  stickers_[front][low_right] = dlr_org;
  stickers_[up][up_right] = fur_org;
  stickers_[up][low_right] = flr_org;
  stickers_[down][up_right] = bll_org;
  stickers_[down][low_right] = bul_org;
  stickers_[back][up_left] = ulr_org;
  stickers_[back][low_left] = uur_org;
}


void Cube::MoveB() {
  Color bur_org = stickers_[back][up_right];
  Color bul_org = stickers_[back][up_left];
  Color blr_org = stickers_[back][low_right];
  Color bll_org = stickers_[back][low_left];

  stickers_[back][up_right] = bul_org;
  stickers_[back][up_left] = bll_org;
  stickers_[back][low_left] = blr_org;
  stickers_[back][low_right] = bur_org;

  Color uur_org = stickers_[up][up_right];
  Color uul_org = stickers_[up][up_left];
  Color rur_org = stickers_[right][up_right];
  Color rlr_org = stickers_[right][low_right];
  Color lul_org = stickers_[left][up_left];
  Color lll_org = stickers_[left][low_left];
  Color dlr_org = stickers_[down][low_right];
  Color dll_org = stickers_[down][low_left];

  stickers_[up][up_left] = rur_org;
  stickers_[up][up_right] = rlr_org;
  stickers_[right][up_right] = dlr_org;
  stickers_[right][low_right] = dll_org;
  stickers_[left][up_left] = uur_org;
  stickers_[left][low_left] = uul_org;
  stickers_[down][low_left] = lul_org;
  stickers_[down][low_right] = lll_org;
}

ID Cube::GetID() const {
  std::string id;
  for (size_t face = 0; face < kNumFaces; face++) {
    for (size_t corner = 0; corner < kNumCornersPerFace; corner++) {
      id += ColorToChar(stickers_[face][corner]);
    }
  }
  return id;
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