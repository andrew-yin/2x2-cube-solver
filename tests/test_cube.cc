#include "core/cube.h"

#include <catch2/catch.hpp>

using namespace cubesolver;

TEST_CASE("Constructor based on front, up, and left colors") {
  SECTION("Red, kWhite, kGreen colors") {
    Color front_col = kRed;
    Color up_col = kWhite;
    Color left_col = kGreen;
    Cube cube(front_col, up_col, left_col);

    for (size_t i = 0; i < kNumCornersPerFace; i++) {
      REQUIRE(cube.stickers_[kFront][i] == kRed);
      REQUIRE(cube.stickers_[kBack][i] == kOrange);
      REQUIRE(cube.stickers_[kLeft][i] == kGreen);
      REQUIRE(cube.stickers_[kRight][i] == kBlue);
      REQUIRE(cube.stickers_[kUp][i] == kWhite);
      REQUIRE(cube.stickers_[kDown][i] == kYellow);
    }
  }

  SECTION("Remaining three (kOrange, kYellow, kBlue) colors") {
    Color front_col = kBlue;
    Color up_col = kYellow;
    Color left_col = kOrange;
    Cube cube(front_col, up_col, left_col);

    for (size_t i = 0; i < kNumCornersPerFace; i++) {
      REQUIRE(cube.stickers_[kFront][i] == kBlue);
      REQUIRE(cube.stickers_[kBack][i] == kGreen);
      REQUIRE(cube.stickers_[kLeft][i] == kOrange);
      REQUIRE(cube.stickers_[kRight][i] == kRed);
      REQUIRE(cube.stickers_[kUp][i] == kYellow);
      REQUIRE(cube.stickers_[kDown][i] == kWhite);
    }
  }
}

TEST_CASE("Constructor based on stickers 2D array") {
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[kFront][kUpperLeft] = kYellow;
  stickers[kFront][kUpperRight] = kBlue;
  stickers[kFront][kLowerLeft] = kWhite;
  stickers[kFront][kLowerRight] = kOrange;
  stickers[kRight][kUpperLeft] = kOrange;
  stickers[kRight][kUpperRight] = kBlue;
  stickers[kRight][kLowerLeft] = kYellow;
  stickers[kRight][kLowerRight] = kYellow;
  stickers[kUp][kUpperLeft] = kOrange;
  stickers[kUp][kUpperRight] = kRed;
  stickers[kUp][kLowerLeft] = kGreen;
  stickers[kUp][kLowerRight] = kWhite;
  stickers[kLeft][kUpperLeft] = kWhite;
  stickers[kLeft][kUpperRight] = kOrange;
  stickers[kLeft][kLowerLeft] = kGreen;
  stickers[kLeft][kLowerRight] = kGreen;
  stickers[kBack][kUpperLeft] = kWhite;
  stickers[kBack][kUpperRight] = kGreen;
  stickers[kBack][kLowerLeft] = kRed;
  stickers[kBack][kLowerRight] = kYellow;
  stickers[kDown][kUpperLeft] = kRed;
  stickers[kDown][kUpperRight] = kBlue;
  stickers[kDown][kLowerLeft] = kRed;
  stickers[kDown][kLowerRight] = kBlue;

  Cube cube(stickers);
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
    }
  }
}

TEST_CASE("Move down") {
  Cube cube(kGreen, kWhite, kOrange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kOrange;
    stickers[kFront][kLowerRight] = kOrange;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kGreen;
    stickers[kRight][kLowerRight] = kGreen;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kWhite;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kBlue;
    stickers[kLeft][kLowerRight] = kBlue;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kRed;
    stickers[kBack][kLowerRight] = kRed;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kYellow;

    cube.MoveD();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kBlue;
    stickers[kFront][kLowerRight] = kBlue;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kOrange;
    stickers[kRight][kLowerRight] = kOrange;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kWhite;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kRed;
    stickers[kLeft][kLowerRight] = kRed;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kGreen;
    stickers[kBack][kLowerRight] = kGreen;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kYellow;

    cube.MoveD();
    cube.MoveD();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("90 degree counterclockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kRed;
    stickers[kFront][kLowerRight] = kRed;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kBlue;
    stickers[kRight][kLowerRight] = kBlue;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kWhite;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kGreen;
    stickers[kLeft][kLowerRight] = kGreen;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kOrange;
    stickers[kBack][kLowerRight] = kOrange;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kYellow;

    cube.MoveD();
    cube.MoveD();
    cube.MoveD();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }
}

TEST_CASE("Move right") {
  Cube cube(kGreen, kWhite, kOrange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kYellow;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kYellow;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kRed;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kGreen;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kGreen;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kOrange;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kWhite;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kWhite;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kBlue;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kBlue;

    cube.MoveR();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kBlue;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kBlue;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kRed;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kYellow;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kYellow;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kOrange;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kGreen;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kGreen;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kWhite;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kWhite;

    cube.MoveR();
    cube.MoveR();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("90 degree counterclockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kWhite;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kWhite;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kRed;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kRed;
    stickers[kUp][kUpperLeft] = kWhite;
    stickers[kUp][kUpperRight] = kBlue;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kBlue;
    stickers[kLeft][kUpperLeft] = kOrange;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kOrange;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kYellow;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kYellow;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kGreen;
    stickers[kDown][kLowerLeft] = kYellow;
    stickers[kDown][kLowerRight] = kGreen;

    cube.MoveR();
    cube.MoveR();
    cube.MoveR();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }
}

TEST_CASE("Move back") {
  Cube cube(kGreen, kWhite, kOrange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kGreen;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kYellow;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kYellow;
    stickers[kUp][kUpperLeft] = kRed;
    stickers[kUp][kUpperRight] = kRed;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kWhite;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kWhite;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kBlue;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kOrange;
    stickers[kDown][kLowerRight] = kOrange;

    cube.MoveB();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kGreen;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kOrange;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kOrange;
    stickers[kUp][kUpperLeft] = kYellow;
    stickers[kUp][kUpperRight] = kYellow;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kRed;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kRed;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kBlue;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kWhite;
    stickers[kDown][kLowerRight] = kWhite;

    cube.MoveB();
    cube.MoveB();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("90 degree counterclockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[kFront][kUpperLeft] = kGreen;
    stickers[kFront][kUpperRight] = kGreen;
    stickers[kFront][kLowerLeft] = kGreen;
    stickers[kFront][kLowerRight] = kGreen;
    stickers[kRight][kUpperLeft] = kRed;
    stickers[kRight][kUpperRight] = kWhite;
    stickers[kRight][kLowerLeft] = kRed;
    stickers[kRight][kLowerRight] = kWhite;
    stickers[kUp][kUpperLeft] = kOrange;
    stickers[kUp][kUpperRight] = kOrange;
    stickers[kUp][kLowerLeft] = kWhite;
    stickers[kUp][kLowerRight] = kWhite;
    stickers[kLeft][kUpperLeft] = kYellow;
    stickers[kLeft][kUpperRight] = kOrange;
    stickers[kLeft][kLowerLeft] = kYellow;
    stickers[kLeft][kLowerRight] = kOrange;
    stickers[kBack][kUpperLeft] = kBlue;
    stickers[kBack][kUpperRight] = kBlue;
    stickers[kBack][kLowerLeft] = kBlue;
    stickers[kBack][kLowerRight] = kBlue;
    stickers[kDown][kUpperLeft] = kYellow;
    stickers[kDown][kUpperRight] = kYellow;
    stickers[kDown][kLowerLeft] = kRed;
    stickers[kDown][kLowerRight] = kRed;

    cube.MoveB();
    cube.MoveB();
    cube.MoveB();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }
}

TEST_CASE("GetID") {
  Cube cube(kGreen, kWhite, kOrange);
  REQUIRE(cube.GetID() == "ggggbbbboooorrrrwwwwyyyy");

  cube.MoveB();
  REQUIRE(cube.GetID() == "ggggbbbbwoworyryrrwwyyoo");

  cube.MoveR();
  REQUIRE(cube.GetID() == "gygowbrbwoworryyrgwgybob");

  cube.MoveD();
  REQUIRE(cube.GetID() == "gywowbyyworbrrgorgwgoybb");
}

TEST_CASE("Equality operator") {
  Cube cube1(kBlue, kYellow, kOrange);
  Cube cube2(kBlue, kYellow, kOrange);
  REQUIRE(cube1 == cube2);

  cube1.MoveB();
  cube2.MoveB();
  REQUIRE(cube1 == cube2);

  cube1.MoveD();
  cube2.MoveD();
  REQUIRE(cube1 == cube2);

  cube1.MoveR();
  cube2.MoveR();
  REQUIRE(cube1 == cube2);

  cube1.MoveR();
  cube2.MoveD();
  REQUIRE(!(cube1 == cube2));
}