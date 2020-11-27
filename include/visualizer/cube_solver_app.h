#pragma once


#include <vector>

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
  /*
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;
   */

  const double kWindowWidth = 1600;
  const double kWindowHeight = 900;

  const double kStickerWidth = 100;

 private:
  std::vector<std::vector<Sticker>> stickers_;
};

}

}