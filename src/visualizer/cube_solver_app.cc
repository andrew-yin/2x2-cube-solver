#include "visualizer/cube_solver_app.h"

#include <core/corner.h>
#include <core/cube.h>
#include <core/face.h>

namespace cubesolver {

namespace visualizer {

CubeSolverApp::CubeSolverApp() : current_state_(select_red) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void CubeSolverApp::setup() {
  glm::vec2 top_left_corner(2 * kStickerWidth,
                            kWindowHeight / 2 - kStickerWidth);
  CreateFace(left, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, 0);
  CreateFace(front, top_left_corner);

  top_left_corner += glm::vec2(0, -2 * kStickerWidth);
  CreateFace(up, top_left_corner);

  top_left_corner += glm::vec2(0, 4 * kStickerWidth);
  CreateFace(down, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, -2 * kStickerWidth);
  CreateFace(right, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, 0);
  CreateFace(back, top_left_corner);
}

void CubeSolverApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      stickers_[i][j].Draw();
    }
  }
}

void CubeSolverApp::CreateFace(const Face& face,
                               const glm::vec2& top_left_corner) {
  stickers_[face][up_left] = Sticker(top_left_corner, kStickerWidth);
  stickers_[face][low_left] =
      Sticker(top_left_corner + glm::vec2(0, kStickerWidth), kStickerWidth);
  stickers_[face][low_right] = Sticker(
      top_left_corner + glm::vec2(kStickerWidth, kStickerWidth), kStickerWidth);
  stickers_[face][up_right] =
      Sticker(top_left_corner + glm::vec2(kStickerWidth, 0), kStickerWidth);
}

void CubeSolverApp::mouseDown(ci::app::MouseEvent event) {
  if (current_state_ != solved) {
    glm::vec2 mouse_pos = event.getPos();
    for (size_t i = 0; i < kNumFaces; i++) {
      for (size_t j = 0; j < kNumCornersPerFace; j++) {
        Sticker& sticker = stickers_[i][j];
        if (sticker.IsWithinSticker(mouse_pos)) {
          Color color;
          switch (current_state_) {
            case select_red:
              color = red;
              break;
            case select_orange:
              color = orange;
              break;
            case select_blue:
              color = blue;
              break;
            case select_green:
              color = green;
              break;
            case select_yellow:
              color = yellow;
              break;
          }
          if (sticker.GetColor() == white) {
            stickers_[i][j].SetColor(color);
            color_count_++;
          }

          if (color_count_ == kNumCornersPerFace) {
            color_count_ = 0;
            ++current_state_;
          }
        }
      }
    }
  }
}

}  // namespace visualizer

}  // namespace cubesolver