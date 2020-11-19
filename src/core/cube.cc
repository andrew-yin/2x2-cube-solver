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

  uur_ = uul_org;
  uul_ = udl_org;
  udl_ = udr_org;
  udr_ = uur_org;

  Color fur_org = fur_;
  Color ful_org = ful_;
  Color lul_org = lul_;
  Color lur_org = lur_;
  Color rul_org = rul_;
  Color rur_org = rur_;
  Color bur_org = bur_;
  Color bul_org = bul_;

  ful_ = rul_org;
  fur_ = rur_org;
  lur_ = fur_org;
  lul_ = ful_org;
  rul_ = bul_org;
  rur_ = bur_org;
  bul_ = lul_org;
  bur_ = lur_org;
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
  Color dur_org = dur_;
  Color dul_org = dul_;
  Color ddr_org = ddr_;
  Color ddl_org = ddl_;

  dur_ = dul_org;
  dul_ = ddl_org;
  ddl_ = ddr_org;
  ddr_ = dur_org;

  Color fdr_org = fdr_;
  Color fdl_org = fdl_;
  Color ldl_org = ldl_;
  Color ldr_org = ldr_;
  Color rdl_org = rdl_;
  Color rdr_org = rdr_;
  Color bdr_org = bdr_;
  Color bdl_org = bdl_;

  fdl_ = ldl_org;
  fdr_ = ldr_org;
  ldr_ = bdr_org;
  ldl_ = bdl_org;
  rdl_ = fdl_org;
  rdr_ = fdr_org;
  bdl_ = rdl_org;
  bdr_ = rdr_org;
}

void Cube::MoveDP() {
  MoveD();
  MoveD();
  MoveD();
}

void Cube::MoveD2() {
  MoveD();
  MoveD();
}

void Cube::MoveL() {
  Color lur_org = lur_;
  Color lul_org = lul_;
  Color ldr_org = ldr_;
  Color ldl_org = ldl_;

  lur_ = lul_org;
  lul_ = ldl_org;
  ldl_ = ldr_org;
  ldr_ = lur_org;

  Color uul_org = uul_;
  Color udl_org = udl_;
  Color ful_org = ful_;
  Color fdl_org = fdl_;
  Color bur_org = bur_;
  Color bdr_org = bdr_;
  Color dul_org = dul_;
  Color ddl_org = ddl_;

  ful_ = uul_org;
  fdl_ = udl_org;
  uul_ = bdr_org;
  udl_ = bur_org;
  dul_ = ful_org;
  ddl_ = fdl_org;
  bur_ = ddl_org;
  bdr_ = dul_org;
}

void Cube::MoveLP() {
  MoveL();
  MoveL();
  MoveL();
}

void Cube::MoveL2() {
  MoveL();
  MoveL();
}

void Cube::MoveR() {
  Color rur_org = rur_;
  Color rul_org = rul_;
  Color rdr_org = rdr_;
  Color rdl_org = rdl_;

  rur_ = rul_org;
  rul_ = rdl_org;
  rdl_ = rdr_org;
  rdr_ = rur_org;

  Color uur_org = uur_;
  Color udr_org = udr_;
  Color fur_org = fur_;
  Color fdr_org = fdr_;
  Color bul_org = bul_;
  Color bdl_org = bdl_;
  Color dur_org = dur_;
  Color ddr_org = ddr_;

  fur_ = dur_org;
  fdr_ = ddr_org;
  uur_ = fur_org;
  udr_ = fdr_org;
  dur_ = bdl_org;
  ddr_ = bul_org;
  bul_ = udr_org;
  bdl_ = uur_org;
}

void Cube::MoveRP() {
  MoveR();
  MoveR();
  MoveR();
}

void Cube::MoveR2() {
  MoveR();
  MoveR();
}

void Cube::MoveB() {
  Color bur_org = bur_;
  Color bul_org = bul_;
  Color bdr_org = bdr_;
  Color bdl_org = bdl_;

  bur_ = bul_org;
  bul_ = bdl_org;
  bdl_ = bdr_org;
  bdr_ = bur_org;

  Color uur_org = uur_;
  Color uul_org = uul_;
  Color rur_org = rur_;
  Color rdr_org = rdr_;
  Color lul_org = lul_;
  Color ldl_org = ldl_;
  Color ddr_org = ddr_;
  Color ddl_org = ddl_;

  uul_ = rur_org;
  uur_ = rdr_org;
  rur_ = ddr_org;
  rdr_ = ddl_org;
  lul_ = uur_org;
  ldl_ = uul_org;
  ddl_ = lul_org;
  ddr_ = ldl_org;
}

void Cube::MoveBP() {
  MoveB();
  MoveB();
  MoveB();
}

void Cube::MoveB2() {
  MoveB();
  MoveB();
}

void Cube::MoveF() {
  Color ful_org = ful_;
  Color fur_org = fur_;
  Color fdl_org = fdl_;
  Color fdr_org = fdr_;

  ful_ = fdl_org;
  fur_ = ful_org;
  fdl_ = fdr_org;
  fdr_ = fur_org;

  Color udl_org = udl_;
  Color udr_org = udr_;
  Color rul_org = rul_;
  Color rdl_org = rdl_;
  Color lur_org = lur_;
  Color ldr_org = ldr_;
  Color dul_org = dul_;
  Color dur_org = dur_;

  udl_ = ldr_org;
  udr_ = lur_org;
  rul_ = udl_org;
  rdl_ = udr_org;
  lur_ = dul_org;
  ldr_ = dur_org;
  dul_ = rdl_org;
  dur_ = rul_org;
}

void Cube::MoveFP() {
  MoveF();
  MoveF();
  MoveF();
}

void Cube::MoveF2() {
  MoveF();
  MoveF();
}

bool Cube::operator==(const Cube &b) const {
  return (ful_ == b.ful_) && (fur_ == b.fur_) && (fdl_ == b.fdl_) && (fdr_ == b.fdr_) && (lul_ == b.lul_)
      && (lur_ == b.lur_) && (ldl_ == b.ldl_) && (ldr_ == b.ldr_) && (uul_ == b.uul_) && (uur_ == b.uur_)
      && (udl_ == b.udl_) && (udr_ == b.udr_) && (rul_ == b.rul_) && (rur_ == b.rur_) && (rdl_ == b.rdl_)
      && (rdr_ == b.rdr_) && (dul_ == b.dul_) && (dur_ == b.dur_) && (ddl_ == b.ddl_) && (ddr_ == b.ddr_)
      && (bul_ == b.bul_) && (bur_ == b.bur_) && (bdl_ == b.bdl_) && (bdr_ == b.bdr_);
}

}