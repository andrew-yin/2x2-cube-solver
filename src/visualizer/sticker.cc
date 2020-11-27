#include "visualizer/sticker.h"

#include <cinder/gl/gl.h>

namespace cubesolver {

namespace visualizer {

Sticker::Sticker(const glm::vec2& top_left_corner, const double& width)
    : box_(top_left_corner, top_left_corner + glm::vec2(width, width)),
      color_(white) {
}

void Sticker::Draw() const {
  switch (color_) {
    case yellow:
      ci::gl::color(ci::Color("yellow"));
      break;
    case red:
      ci::gl::color(ci::Color("red"));
      break;
    case orange:
      ci::gl::color(ci::Color("orange"));
      break;
    case blue:
      ci::gl::color(ci::Color("blue"));
      break;
    case green:
      ci::gl::color(ci::Color("green"));
      break;
    case white:
      ci::gl::color(ci::Color("white"));
      break;
  }

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

bool Sticker::IsWithinSticker(const glm::vec2& pos) const {
  double pos_x = pos.x;
  double pos_y = pos.y;

  double left_bound = box_.getX1();
  double right_bound = box_.getX2();
  double up_bound = box_.getY1();
  double low_bound = box_.getY2();

  return (pos_x > left_bound && pos_x < right_bound) &&
         (pos_y > up_bound && pos_y < low_bound);
}

}  // namespace visualizer

}  // namespace cubesolver