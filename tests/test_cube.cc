#include "core/cube.h"

#include <catch2/catch.hpp>

using namespace cubesolver;

TEST_CASE("Constructor based on front, up, and left colors") {
  SECTION("Red, white, green colors") {
    Color front_col = red;
    Color up_col = white;
    Color left_col = green;
    Cube cube(front_col, up_col, left_col);

    for (size_t i = 0; i < kNumCornersPerFace; i++) {
      REQUIRE(cube.stickers_[front][i] == red);
      REQUIRE(cube.stickers_[back][i] == orange);
      REQUIRE(cube.stickers_[left][i] == green);
      REQUIRE(cube.stickers_[right][i] == blue);
      REQUIRE(cube.stickers_[up][i] == white);
      REQUIRE(cube.stickers_[down][i] == yellow);
    }
  }

  SECTION("Remaining three (orange, yellow, blue) colors") {
    Color front_col = blue;
    Color up_col = yellow;
    Color left_col = orange;
    Cube cube(front_col, up_col, left_col);

    for (size_t i = 0; i < kNumCornersPerFace; i++) {
      REQUIRE(cube.stickers_[front][i] == blue);
      REQUIRE(cube.stickers_[back][i] == green);
      REQUIRE(cube.stickers_[left][i] == orange);
      REQUIRE(cube.stickers_[right][i] == red);
      REQUIRE(cube.stickers_[up][i] == yellow);
      REQUIRE(cube.stickers_[down][i] == white);
    }
  }
}

TEST_CASE("Constructor based on stickers 2D array") {
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
  stickers[front][up_left] = yellow;
  stickers[front][up_right] = blue;
  stickers[front][low_left] = white;
  stickers[front][low_right] = orange;
  stickers[right][up_left] = orange;
  stickers[right][up_right] = blue;
  stickers[right][low_left] = yellow;
  stickers[right][low_right] = yellow;
  stickers[up][up_left] = orange;
  stickers[up][up_right] = red;
  stickers[up][low_left] = green;
  stickers[up][low_right] = white;
  stickers[left][up_left] = white;
  stickers[left][up_right] = orange;
  stickers[left][low_left] = green;
  stickers[left][low_right] = green;
  stickers[back][up_left] = white;
  stickers[back][up_right] = green;
  stickers[back][low_left] = red;
  stickers[back][low_right] = yellow;
  stickers[down][up_left] = red;
  stickers[down][up_right] = blue;
  stickers[down][low_left] = red;
  stickers[down][low_right] = blue;

  Cube cube(stickers);
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
    }
  }
}

TEST_CASE("Move down") {
  Cube cube(green, white, orange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = orange;
    stickers[front][low_right] = orange;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = green;
    stickers[right][low_right] = green;
    stickers[up][up_left] = white;
    stickers[up][up_right] = white;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = blue;
    stickers[left][low_right] = blue;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = red;
    stickers[back][low_right] = red;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = yellow;

    cube.MoveD();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = blue;
    stickers[front][low_right] = blue;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = orange;
    stickers[right][low_right] = orange;
    stickers[up][up_left] = white;
    stickers[up][up_right] = white;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = red;
    stickers[left][low_right] = red;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = green;
    stickers[back][low_right] = green;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = yellow;

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
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = red;
    stickers[front][low_right] = red;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = blue;
    stickers[right][low_right] = blue;
    stickers[up][up_left] = white;
    stickers[up][up_right] = white;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = green;
    stickers[left][low_right] = green;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = orange;
    stickers[back][low_right] = orange;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = yellow;

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
  Cube cube(green, white, orange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = yellow;
    stickers[front][low_left] = green;
    stickers[front][low_right] = yellow;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = red;
    stickers[right][low_right] = red;
    stickers[up][up_left] = white;
    stickers[up][up_right] = green;
    stickers[up][low_left] = white;
    stickers[up][low_right] = green;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = orange;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = white;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = white;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = blue;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = blue;

    cube.MoveR();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = blue;
    stickers[front][low_left] = green;
    stickers[front][low_right] = blue;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = red;
    stickers[right][low_right] = red;
    stickers[up][up_left] = white;
    stickers[up][up_right] = yellow;
    stickers[up][low_left] = white;
    stickers[up][low_right] = yellow;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = orange;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = green;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = green;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = white;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = white;

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
    stickers[front][up_left] = green;
    stickers[front][up_right] = white;
    stickers[front][low_left] = green;
    stickers[front][low_right] = white;
    stickers[right][up_left] = red;
    stickers[right][up_right] = red;
    stickers[right][low_left] = red;
    stickers[right][low_right] = red;
    stickers[up][up_left] = white;
    stickers[up][up_right] = blue;
    stickers[up][low_left] = white;
    stickers[up][low_right] = blue;
    stickers[left][up_left] = orange;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = orange;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = yellow;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = yellow;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = green;
    stickers[down][low_left] = yellow;
    stickers[down][low_right] = green;

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
  Cube cube(green, white, orange);

  SECTION("90 degree clockwise turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = green;
    stickers[front][low_right] = green;
    stickers[right][up_left] = red;
    stickers[right][up_right] = yellow;
    stickers[right][low_left] = red;
    stickers[right][low_right] = yellow;
    stickers[up][up_left] = red;
    stickers[up][up_right] = red;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = white;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = white;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = blue;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = orange;
    stickers[down][low_right] = orange;

    cube.MoveB();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        REQUIRE(stickers[i][j] == cube.stickers_[i][j]);
      }
    }
  }

  SECTION("180 degree turn") {
    std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers;
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = green;
    stickers[front][low_right] = green;
    stickers[right][up_left] = red;
    stickers[right][up_right] = orange;
    stickers[right][low_left] = red;
    stickers[right][low_right] = orange;
    stickers[up][up_left] = yellow;
    stickers[up][up_right] = yellow;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = red;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = red;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = blue;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = white;
    stickers[down][low_right] = white;

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
    stickers[front][up_left] = green;
    stickers[front][up_right] = green;
    stickers[front][low_left] = green;
    stickers[front][low_right] = green;
    stickers[right][up_left] = red;
    stickers[right][up_right] = white;
    stickers[right][low_left] = red;
    stickers[right][low_right] = white;
    stickers[up][up_left] = orange;
    stickers[up][up_right] = orange;
    stickers[up][low_left] = white;
    stickers[up][low_right] = white;
    stickers[left][up_left] = yellow;
    stickers[left][up_right] = orange;
    stickers[left][low_left] = yellow;
    stickers[left][low_right] = orange;
    stickers[back][up_left] = blue;
    stickers[back][up_right] = blue;
    stickers[back][low_left] = blue;
    stickers[back][low_right] = blue;
    stickers[down][up_left] = yellow;
    stickers[down][up_right] = yellow;
    stickers[down][low_left] = red;
    stickers[down][low_right] = red;

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
  Cube cube(green, white, orange);
  REQUIRE(cube.GetID() == "ggggbbbboooorrrrwwwwyyyy");

  cube.MoveB();
  REQUIRE(cube.GetID() == "ggggbbbbwoworyryrrwwyyoo");

  cube.MoveR();
  REQUIRE(cube.GetID() == "gygowbrbwoworryyrgwgybob");

  cube.MoveD();
  REQUIRE(cube.GetID() == "gywowbyyworbrrgorgwgoybb");
}

TEST_CASE("Equality operator") {
  Cube cube1(blue, yellow, orange);
  Cube cube2(blue, yellow, orange);
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