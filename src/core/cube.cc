#include "core/cube.h"

namespace cubesolver {

Cube::Cube()
    : ful_(green),
      fur_(green),
      fdl_(green),
      fdr_(green),
      bul_(blue),
      bur_(blue),
      bdl_(blue),
      bdr_(blue),
      lur_(orange),
      lul_(orange),
      ldl_(orange),
      ldr_(orange),
      uul_(white),
      uur_(white),
      udl_(white),
      udr_(white),
      dul_(yellow),
      dur_(yellow),
      ddl_(yellow),
      ddr_(yellow),
      rul_(red),
      rur_(red),
      rdl_(red),
      rdr_(red) {}

Cube::Cube(Color ful,
           Color fur,
           Color fdl,
           Color fdr,
           Color bul,
           Color bur,
           Color bdl,
           Color bdr,
           Color lur,
           Color lul,
           Color ldl,
           Color ldr,
           Color rul,
           Color rur,
           Color rdl,
           Color rdr,
           Color uur,
           Color uul,
           Color udl,
           Color udr,
           Color dur,
           Color dul,
           Color ddl,
           Color ddr)
    : ful_(ful),
      fur_(fur),
      fdl_(fdl),
      fdr_(fdr),
      bul_(bul),
      bur_(bur),
      bdl_(bdl),
      bdr_(bdr),
      lur_(lur),
      lul_(lul),
      ldl_(ldl),
      ldr_(ldr),
      rul_(rul),
      rur_(rur),
      rdl_(rdl),
      rdr_(rdr),
      uur_(uur),
      uul_(uul),
      udl_(udl),
      udr_(udr),
      dur_(dur),
      dul_(dul),
      ddl_(ddl),
      ddr_(ddr) {}

void Cube::MoveU() {
  Color uur_org = uur_;
  Color uul_org = uul_;
  Color udr_org = udr_;
  Color udl_org = udl_;
  Color fur_org = fur_;
  Color ful_org = ful_;
  Color lul_org = lul_;
  Color lur_org = lur_;
  Color rul_org = rul_;
  Color rur_org = rur_;
  Color bur_org = bur_;
  Color bul_org = bul_;

  uur_ = uul_org;
  uul_ = udl_org;
  udl_ = udr_org;
  udr_ = uur_org;

  ful_ = fur_org;
  lur_ = ful_org;
  lul_ = lur_org;
  bur_ = lul_org;
  bul_ = bur_org;
  rur_ = bul_org;
  rul_ = rur_org;
  fur_ = rul_org;
}

void Cube::MoveUP() {
  MoveU();
  MoveU();
  MoveU();
}
void Cube::MoveU2() {
  MoveU();
  MoveU();
}

void Cube::MoveD() {

}

void Cube::MoveDP() {

}

void Cube::MoveD2() {

}

void Cube::MoveL() {

}

void Cube::MoveLP() {

}

void Cube::MoveL2() {

}

void Cube::MoveR() {

}

void Cube::MoveRP() {

}

void Cube::MoveR2() {

}

void Cube::MoveB() {

}

void Cube::MoveBP() {

}

void Cube::MoveB2() {

}

void Cube::MoveF() {

}

void Cube::MoveFP() {

}

void Cube::MoveF2() {

}

}