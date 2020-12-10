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
  CreateFace(kLeft, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, 0);
  CreateFace(kFront, top_left_corner);

  top_left_corner += glm::vec2(0, -2 * kStickerWidth);
  CreateFace(kUp, top_left_corner);

  top_left_corner += glm::vec2(0, 4 * kStickerWidth);
  CreateFace(kDown, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, -2 * kStickerWidth);
  CreateFace(kRight, top_left_corner);

  top_left_corner += glm::vec2(2 * kStickerWidth, 0);
  CreateFace(kBack, top_left_corner);
}

void CubeSolverApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  DrawMessages();

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
          Color color = GetCurrentStateColor();

          Color sticker_color = sticker.GetColor();
          if (sticker_color == kWhite) {
            sticker.SetColor(color);
            color_count_++;
          } else if (sticker_color == color) {
            sticker.SetColor(kWhite);
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

void CubeSolverApp::DrawMessages() const {
  float font_size = 36;
  glm::vec2 instructions_pos(kWindowWidth / 2 - 2 * kStickerWidth,
                             kStickerWidth / 2);
  std::string instructions_msg = GetInstructionsMessage();
  std::string solution_msg = GetSolutionMessage();

  ci::gl::drawStringCentered(instructions_msg, instructions_pos,
                             ci::Color("black"), ci::Font("Arial", font_size));
  ci::gl::drawStringCentered(
      solution_msg,
      glm::vec2(kWindowWidth / 2 + 5 * kStickerWidth, kWindowHeight / 2),
      ci::Color("black"), ci::Font("Arial", 24));

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
}

void CubeSolverApp::CreateFace(const Face& face,
                               const glm::vec2& top_left_corner) {
  stickers_[face][kUpperLeft] = Sticker(top_left_corner, kStickerWidth);
  stickers_[face][kLowerLeft] =
      Sticker(top_left_corner + glm::vec2(0, kStickerWidth), kStickerWidth);
  stickers_[face][kLowerRight] = Sticker(
      top_left_corner + glm::vec2(kStickerWidth, kStickerWidth), kStickerWidth);
  stickers_[face][kUpperRight] =
      Sticker(top_left_corner + glm::vec2(kStickerWidth, 0), kStickerWidth);
}

void CubeSolverApp::Clear() {
  for (size_t i = 0; i < kNumFaces; i++) {
    for (size_t j = 0; j < kNumCornersPerFace; j++) {
      stickers_[i][j].SetColor(kWhite);
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

std::string CubeSolverApp::GetInstructionsMessage() const {
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
  return instructions_msg;
}

std::string CubeSolverApp::GetSolutionMessage() const {
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
  return solution_msg;
}

Color CubeSolverApp::GetCurrentStateColor() const {
  switch (current_state_) {
    case select_red:
      return kRed;
    case select_orange:
      return kOrange;
    case select_blue:
      return kBlue;
    case select_green:
      return kGreen;
    case select_yellow:
      return kYellow;
    default:
      return kWhite;
  }
}

}  // namespace visualizer

}  // namespace cubesolver