#include "visualizer/sticker.h"

#include <cinder/gl/gl.h>

namespace cubesolver {

namespace visualizer {

Sticker::Sticker(const glm::vec2& top_left_corner, const double& width)
    : box_(top_left_corner, top_left_corner + glm::vec2(width, width)), color_(white) {
}

void Sticker::Draw() const {
  ci::Color draw_color;

  switch(color_) {
    case yellow:
      draw_color = ci::Color("yellow");
    case red:
      draw_color = ci::Color("red");
    case orange:
      draw_color = ci::Color("orange");
    case blue:
      draw_color = ci::Color("blue");
    case green:
      draw_color = ci::Color("green");
    case white:
      draw_color = ci::Color("white");
  }

  ci::gl::color(draw_color);
  ci::gl::drawSolidRect(box_);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(box_);
}

void Sticker::SetColor(const Color& color) {
  color_ = color;
}

const Color& Sticker::GetColor() const {
  return color_;
}

}  // namespace visualizer

}  // namespace cubesolver