#pragma once

#include <array>
#include <string>

namespace cubesolver {

typedef std::string ID;

/**
 * Represents the six colors that exist on a cube
 */
enum Color { kWhite, kYellow, kRed, kOrange, kBlue, kGreen };

/**
 * Returns a char representation of a Color enum
 *
 * @param color  The color to get the char representation of
 * @return       The char representing the Color
 */
char ColorToChar(const Color& color);

/**
 * Returns the color of the opposite side of the cube when the cube is in a
 * solved state.
 *
 * @param color  The color specified
 * @return       The color that lies on the opposite face of the color
 *               specified in the cube's solved state.
 */
Color GetOppositeSide(const Color& color);

/**
 * Represents the four locations of each sticker on each face when looking
 * directly at the face
 */
enum Corner { kUpperLeft, kUpperRight, kLowerLeft, kLowerRight };

/**
 * A Enum representation of the six faces of the Rubik's cube.
 */
enum Face { kFront, kBack, kLeft, kRight, kUp, kDown };

/* The number of faces on a Rubik's cube */
const size_t kNumFaces = 6;

/* The number of corner stickers per face on the cube */
const size_t kNumCornersPerFace = 4;

/**
 * A representation of a 2x2x2 Rubik's cube.
 */
struct Cube {
  /**
   * Constructs a solved Rubik's cube based on desired front, up, and left
   * colors
   *
   * @param f_color  The front color
   * @param u_color  The up color
   * @param l_color  The left color
   */
  Cube(const Color& f_color, const Color& u_color, const Color& l_color);

  /**
   * Constructs a Rubik's cube based on a 2D array of the stickers' colors
   *
   * @param stickers  The sticker colors given (see below for details as to
   *                  how the stickers are stored in the array)
   */
  Cube(const std::array<std::array<Color, kNumCornersPerFace>, kNumFaces>&
           stickers);

  /**
   * Various manipulations of the Cube's stickers. Each move is representative
   * of a 90 degree clockwise rotation of the specified face when the face is
   * looked at directly.
   */
  void MoveD();
  void MoveR();
  void MoveB();

  /**
   * The colors of each stickers are stored as stickers_[face][corner]
   * where face is a Face enum representing the face the sticker belongs to
   * and corner is a Corner enum indicating the corner the sticker on the face
   * lies.
   *
   * For example, stickers_[up][kLowerLeft] represents the sticker on the upper
   * face of the Rubik's cube and on the lower left corner of this face when
   * looked at directly.
   */
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> stickers_;

  /**
   * Generates a unique ID corresponding to the current state of the Rubik's
   * cube
   *
   * @return  The unique ID described above
   */
  ID GetID() const;

  bool operator==(const Cube& b) const;
};

}  // namespace cubesolver