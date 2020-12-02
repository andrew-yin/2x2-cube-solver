#pragma once

namespace cubesolver {

namespace visualizer {

/**
 * Enum representation for the different states the application is in
 */
enum AppState {
  /* User currently selecting X-colored stickers */
  select_red,
  select_orange,
  select_blue,
  select_green,
  select_yellow,
  /* User has selected all stickers */
  all_selected,
  /* Application is currently computing a solution to the cube */
  solving,
  /* Application has output a solution */
  solved
};

/**
 * Overloaded increment operator to facilitate progression from an app state to
 * the next
 */
inline AppState& operator++(AppState& state) {
  if (state == solved) {
    state = select_red;
  } else {
    state = static_cast<AppState>(static_cast<int>(state) + 1);
  }
  return state;
}

}  // namespace visualizer

};  // namespace cubesolver