#include "visualizer/cube_solver_app.h"

#include <core/cube.h>

namespace cubesolver {

namespace visualizer {

AppState& operator++(AppState& state) {
  if (state == solved) {
    state = select_red;
  } else {
    state = static_cast<AppState>(static_cast<int>(state) + 1);
  }
  return state;
}

CubeSolverApp::CubeSolverApp() : current_state_(select_red), color_count_(0) {
  ci::app::setWindowSize((int)kWindowWidth, (int)kWindowHeight);
}

void CubeSolverApp::setup() {
  /* Initialize all 6 faces of the cube at their respective locations */
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

  glm::vec2 instructions_pos(kWindowWidth / 2 - 2 * kStickerWidth,
                             kStickerWidth / 2);
  float font_size = 36;

  /* Generate top instruction message based on the app's current state */
  std::string instructions_msg;
  switch (current_state_) {
    case select_red:
      instructions_msg = "Please choose the red stickers.";
      break;
    case select_orange:
      instructions_msg = "Please choose the orange stickers.";
      break;
    case select_blue:
      instructions_msg = "Please choose the blue stickers.";
      break;
    case select_green:
      instructions_msg = "Please choose the green stickers.";
      break;
    case select_yellow:
      instructions_msg = "Please choose the yellow stickers.";
      break;
    case all_selected:
      instructions_msg = "Press Enter to start solving.";
      break;
    case solved:
      instructions_msg =
          "Please view the solution on the right (if one exists).";
      break;
  }

  /* Generate a message for where the solution is to be placed based on the
   * app state */
  std::string solution_msg;
  if (current_state_ == solved) {
    std::string separator = "";
    for (const Move& move : solution_) {
      solution_msg += separator + MoveToString(move);
      separator = " ";
    }
  } else {
    solution_msg = "N/A";
  }

  ci::gl::drawStringCentered(instructions_msg, instructions_pos,
                             ci::Color("black"), ci::Font("Arial", font_size));

  ci::gl::drawStringCentered("Solution",
                             glm::vec2(kWindowWidth / 2 + 5 * kStickerWidth,
                                       kWindowHeight / 2 - kStickerWidth),
                             ci::Color("black"), ci::Font("Arial", font_size));

  ci::gl::drawStringCentered(
      "Press Backspace to clear the whole cube or click once more to reset an "
      "individual sticker.",
      glm::vec2(kWindowWidth / 2 - 2 * kStickerWidth,
                kWindowHeight - kStickerWidth),
      ci::Color("black"), ci::Font("Arial", 20));
  ci::gl::drawStringCentered(
      solution_msg,
      glm::vec2(kWindowWidth / 2 + 5 * kStickerWidth, kWindowHeight / 2),
      ci::Color("black"), ci::Font("Arial", 24));

  /* Draw each individual sticker of the cube */
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      stickers_[i][j].Draw();
    }
  }
}

void CubeSolverApp::mouseDown(ci::app::MouseEvent event) {
  if (current_state_ != solved && current_state_ != all_selected) {
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
            default:
              break;
          }

          Color sticker_color = sticker.GetColor();
          if (sticker_color == white) {
            sticker.SetColor(color);
            color_count_++;
          } else if (sticker_color == color) {
            sticker.SetColor(white);
            color_count_--;
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

void CubeSolverApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      if (current_state_ == all_selected) {
        Solve();
        ++current_state_;
      }
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      Clear();
      break;
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

void CubeSolverApp::Clear() {
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      stickers_[i][j].SetColor(white);
    }
  }
  current_state_ = select_red;
  color_count_ = 0;
}

void CubeSolverApp::Solve() {
  std::array<std::array<Color, kNumCornersPerFace>, kNumFaces> colors;
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      colors[i][j] = stickers_[i][j].GetColor();
    }
  }
  solution_ = solver_.SolveCube(Cube(colors));
}

}  // namespace visualizer

}  // namespace cubesolver