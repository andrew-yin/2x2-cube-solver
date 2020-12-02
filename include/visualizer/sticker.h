#pragma once

#include <cinder/Color.h>
#include <cinder/Rect.h>
#include <core/color.h>

#include <glm/vec2.hpp>

namespace cubesolver {

namespace visualizer {

/**
 * A representation of a Sticker drawn in the Cinder application.
 */
class Sticker {
 public:
  Sticker() = default;
  /**
   * Constructs a sticker at the given location and width.
   *
   * @param top_left_corner  The top left corner of the sticker
   * @param width            The width, in pixels, of the sticker
   */
  Sticker(const glm::vec2& top_left_corner, const double& width);

  void Draw() const;

  void SetColor(const Color& color);
  const Color& GetColor() const;

  /**
   * True if pos is a coordinate within the bounds of the sticker, false
   * otherwise
   */
  bool IsWithinSticker(const glm::vec2& pos) const;

 private:
  ci::Rectf box_;
  Color color_;
};

}  // namespace visualizer

}  // namespace cubesolver