#pragma once

#include <cinder/Color.h>
#include <cinder/Rect.h>
#include <core/color.h>

#include <glm/vec2.hpp>

namespace cubesolver {

namespace visualizer {

class Sticker {
 public:
  Sticker() = default;
  Sticker(const glm::vec2& top_left_corner, const double& width);

  void Draw() const;

  void SetColor(const Color& color);
  const Color& GetColor() const;

  bool IsWithinSticker(const glm::vec2& pos) const;

 private:
  ci::Rectf box_;
  Color color_;
};

}  // namespace visualizer

}  // namespace cubesolver