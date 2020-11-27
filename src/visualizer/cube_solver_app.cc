#include "visualizer/cube_solver_app.h"

#include <core/corner.h>
#include <core/cube.h>
#include <core/face.h>

namespace cubesolver {

namespace visualizer {

CubeSolverApp::CubeSolverApp() : stickers_(kNumFaces, std::vector<Sticker>(kNumCornersPerFace)){
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
}

void CubeSolverApp::setup() {
  glm::vec2 pos(2*kStickerWidth, kWindowHeight/2 - kStickerWidth);

  stickers_[left][up_left] = Sticker(pos, kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[left][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[left][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[left][up_right] = Sticker(pos, kStickerWidth);

  pos.x += kStickerWidth;
  stickers_[front][up_left] = Sticker(pos,kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[front][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[front][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[front][up_right] = Sticker(pos, kStickerWidth);

  pos.x -= kStickerWidth;
  pos.y -= 2*kStickerWidth;
  stickers_[up][up_left] = Sticker(pos,kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[up][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[up][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[up][up_right] = Sticker(pos, kStickerWidth);

  pos.x -= kStickerWidth;
  pos.y += 4*kStickerWidth;
  stickers_[down][up_left] = Sticker(pos,kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[down][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[down][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[down][up_right] = Sticker(pos, kStickerWidth);

  pos.y -= 2*kStickerWidth;
  pos.x += kStickerWidth;
  stickers_[right][up_left] = Sticker(pos,kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[right][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[right][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[right][up_right] = Sticker(pos, kStickerWidth);

  pos.x += kStickerWidth;
  stickers_[back][up_left] = Sticker(pos,kStickerWidth);
  pos.y += kStickerWidth;
  stickers_[back][low_left] = Sticker(pos, kStickerWidth);
  pos.x += kStickerWidth;
  stickers_[back][low_right] = Sticker(pos, kStickerWidth);
  pos.y -= kStickerWidth;
  stickers_[back][up_right] = Sticker(pos, kStickerWidth);
}

void CubeSolverApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  for (std::vector<Sticker> face: stickers_) {
    for (Sticker corner: face) {
      corner.Draw();
    }
  }
}

}

}