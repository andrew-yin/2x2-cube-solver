#pragma once

#include <core/cube.h>
#include <core/face.h>
#include <core/solver.h>

#include <array>

#include "app_state.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sticker.h"

namespace cubesolver {

namespace visualizer {

class CubeSolverApp : public ci::app::App {
 public:
  CubeSolverApp();

  void setup() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowWidth = 1600;
  const double kWindowHeight = 900;

  const double kStickerWidth = 100;

 private:
  std::array<std::array<Sticker, kNumCornersPerFace>, kNumFaces> stickers_;
  AppState current_state_;
  size_t color_count_;
  Solver solver_;
  std::vector<std::string> solution_;

  void CreateFace(const Face& face, const glm::vec2& top_left_corner);
  void Clear();
  void Solve();
};

}  // namespace visualizer

}  // namespace cubesolver