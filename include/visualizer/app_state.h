#pragma once

namespace cubesolver {

namespace visualizer {

enum AppState {
  select_red,
  select_orange,
  select_blue,
  select_green,
  select_yellow,
  solved
};

inline AppState& operator++(AppState& state) {
  if (state == solved) {
    state = select_red;
  }
  else {
    state = static_cast<AppState>(static_cast<int>(state) + 1);
  }
  return state;
}

}

};