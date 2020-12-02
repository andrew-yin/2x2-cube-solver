#pragma once

#include <array>

#include "color.h"

namespace cubesolver {

/* The number of faces on a Rubik's cube */
const size_t kNumFaces = 6;

/* The number of corner stickers per face on the cube */
const size_t kNumCornersPerFace = 4;

/**
 * A representation of a 2x2x2 Rubik's cube.
 */
struct Cube {
  /**
   * Constructs a solved Rubik's cube based on whether or not the parameters
   * given are from the front, up, and left sides or the back, down, and right
   * sides.
   *
   * @param is_ful               True if the colors come from the FUL sides and
   *                             false if the colors come from the BDR sides
   * @param front_or_back_color  The front/back color depending on is_ful
   * @param up_or_down_color     The up/down color depending on is_ful
   * @param left_or_right_color  The left/right color depending on is_ful
   */
  Cube(bool is_ful, const Color& front_or_back_color,
       const Color& left_or_right_color, const Color& up_or_down_color);

  /**
   * Constructs a Rubik's cube based on a 2D array of the stickers' colors
   *
   * @param stickers  The sticker colors given (see below for details as to
   *                  how the stickers are stored in the array)
   */
  explicit Cube(const std::array<std::array<Color, kNumCornersPerFace>,
                                 kNumFaces>& stickers);

  /**
   * Various manipulations of the Cube's stickers. Each move is representative
   * of a 90 degree clockwise rotation of the specified face when the face is
   * looked at directly.
   */
  void MoveU();
  void MoveD();
  void MoveR();
  void MoveL();
  void MoveF();
  void MoveB();

  bool operator==(const Cube& b) const;

  /**
   * The colors of each stickers are stored as stickers_[face][corner]
   * where face is a Face enum representing the face the sticker belongs to
   * and corner is a Corner enum indicating the corner the sticker on the face
   * lies.
   *
   * For example, stickers_[up][low_left] represents the sticker on the upper
   * face of the Rubik's cube and on the lower left corner of this face when
   * looked at directly.
   */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers_;

 private:
  /**
   * Returns the color of the opposite side of the cube when the cube is in a
   * solved state.
   *
   * @param color  The color specified
   * @return       The color that lies on the opposite face of the color
   *               specified in the cube's solved state.
   */
  Color GetOppositeSide(const Color& color) const;
};

}  // namespace cubesolver