#include <visualizer/cube_solver_app.h>

using cubesolver::visualizer::CubeSolverApp;

void prepareSettings(CubeSolverApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(CubeSolverApp, ci::app::RendererGl, prepareSettings);