#include "core/cube.h"

namespace cubesolver {

char ColorToChar(const Color& color) {
  switch (color) {
    case kWhite:
      return 'w';
    case kYellow:
      return 'y';
    case kRed:
      return 'r';
    case kOrange:
      return 'o';
    case kBlue:
      return 'b';
    case kGreen:
      return 'g';
  }
}

Color GetOppositeSide(const Color& color) {
  switch (color) {
    case kWhite:
      return kYellow;
    case kYellow:
      return kWhite;
    case kRed:
      return kOrange;
    case kOrange:
      return kRed;
    case kBlue:
      return kGreen;
    case kGreen:
      return kBlue;
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
    stickers_[kUp][i] = u_color;
    stickers_[kDown][i] = d_col;
    stickers_[kLeft][i] = l_color;
    stickers_[kRight][i] = r_col;
    stickers_[kFront][i] = f_color;
    stickers_[kBack][i] = b_col;
  }
}

void Cube::MoveD() {
  Color dur_org = stickers_[kDown][kUpperRight];
  Color dul_org = stickers_[kDown][kUpperLeft];
  Color dlr_org = stickers_[kDown][kLowerRight];
  Color dll_org = stickers_[kDown][kLowerLeft];

  stickers_[kDown][kUpperRight] = dul_org;
  stickers_[kDown][kUpperLeft] = dll_org;
  stickers_[kDown][kLowerLeft] = dlr_org;
  stickers_[kDown][kLowerRight] = dur_org;

  Color flr_org = stickers_[kFront][kLowerRight];
  Color fll_org = stickers_[kFront][kLowerLeft];
  Color lll_org = stickers_[kLeft][kLowerLeft];
  Color llr_org = stickers_[kLeft][kLowerRight];
  Color rll_org = stickers_[kRight][kLowerLeft];
  Color rlr_org = stickers_[kRight][kLowerRight];
  Color blr_org = stickers_[kBack][kLowerRight];
  Color bll_org = stickers_[kBack][kLowerLeft];

  stickers_[kFront][kLowerLeft] = lll_org;
  stickers_[kFront][kLowerRight] = llr_org;
  stickers_[kLeft][kLowerRight] = blr_org;
  stickers_[kLeft][kLowerLeft] = bll_org;
  stickers_[kRight][kLowerLeft] = fll_org;
  stickers_[kRight][kLowerRight] = flr_org;
  stickers_[kBack][kLowerLeft] = rll_org;
  stickers_[kBack][kLowerRight] = rlr_org;
}

void Cube::MoveR() {
  Color rur_org = stickers_[kRight][kUpperRight];
  Color rul_org = stickers_[kRight][kUpperLeft];
  Color rlr_org = stickers_[kRight][kLowerRight];
  Color rll_org = stickers_[kRight][kLowerLeft];

  stickers_[kRight][kUpperRight] = rul_org;
  stickers_[kRight][kUpperLeft] = rll_org;
  stickers_[kRight][kLowerLeft] = rlr_org;
  stickers_[kRight][kLowerRight] = rur_org;

  Color uur_org = stickers_[kUp][kUpperRight];
  Color ulr_org = stickers_[kUp][kLowerRight];
  Color fur_org = stickers_[kFront][kUpperRight];
  Color flr_org = stickers_[kFront][kLowerRight];
  Color bul_org = stickers_[kBack][kUpperLeft];
  Color bll_org = stickers_[kBack][kLowerLeft];
  Color dur_org = stickers_[kDown][kUpperRight];
  Color dlr_org = stickers_[kDown][kLowerRight];

  stickers_[kFront][kUpperRight] = dur_org;
  stickers_[kFront][kLowerRight] = dlr_org;
  stickers_[kUp][kUpperRight] = fur_org;
  stickers_[kUp][kLowerRight] = flr_org;
  stickers_[kDown][kUpperRight] = bll_org;
  stickers_[kDown][kLowerRight] = bul_org;
  stickers_[kBack][kUpperLeft] = ulr_org;
  stickers_[kBack][kLowerLeft] = uur_org;
}


void Cube::MoveB() {
  Color bur_org = stickers_[kBack][kUpperRight];
  Color bul_org = stickers_[kBack][kUpperLeft];
  Color blr_org = stickers_[kBack][kLowerRight];
  Color bll_org = stickers_[kBack][kLowerLeft];

  stickers_[kBack][kUpperRight] = bul_org;
  stickers_[kBack][kUpperLeft] = bll_org;
  stickers_[kBack][kLowerLeft] = blr_org;
  stickers_[kBack][kLowerRight] = bur_org;

  Color uur_org = stickers_[kUp][kUpperRight];
  Color uul_org = stickers_[kUp][kUpperLeft];
  Color rur_org = stickers_[kRight][kUpperRight];
  Color rlr_org = stickers_[kRight][kLowerRight];
  Color lul_org = stickers_[kLeft][kUpperLeft];
  Color lll_org = stickers_[kLeft][kLowerLeft];
  Color dlr_org = stickers_[kDown][kLowerRight];
  Color dll_org = stickers_[kDown][kLowerLeft];

  stickers_[kUp][kUpperLeft] = rur_org;
  stickers_[kUp][kUpperRight] = rlr_org;
  stickers_[kRight][kUpperRight] = dlr_org;
  stickers_[kRight][kLowerRight] = dll_org;
  stickers_[kLeft][kUpperLeft] = uur_org;
  stickers_[kLeft][kLowerLeft] = uul_org;
  stickers_[kDown][kLowerLeft] = lul_org;
  stickers_[kDown][kLowerRight] = lll_org;
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
  bool isEqual = true;
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      if (stickers_[i][j] != b.stickers_[i][j]) {
        isEqual = false;
        break;
      }
    }
  }

  return isEqual;
}

}  // namespace cubesolver