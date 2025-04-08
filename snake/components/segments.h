//
// Created by Danylo Shevchenko on 07.04.25.
//

#pragma once
#include "../config.h"
#include "transform.h"

namespace snake {

class Head {
 public:
  Direction queued_dir_ = {};
  float move_delay_secs_ = 0.2f;
  bool boost_ = false;

  bool Update() {
    frames_since_last_move_++;

    if (static_cast<float>(frames_since_last_move_) >=
        kFPS * GetMoveDelaySecs()) {
      frames_since_last_move_ = 0;
      return true;
    }

    return false;
  }

  void ForceUpdate() {
    frames_since_last_move_ = static_cast<int>(kFPS * GetMoveDelaySecs()) + 1;
  }

 private:
  int frames_since_last_move_ = 0;

  [[nodiscard]] float GetMoveDelaySecs() const {
    const auto multiplier = boost_ ? 0.5f : 1.f;
    return move_delay_secs_ * multiplier;
  }
};

class Tail {};

class Body {};

class Part {};
}  // namespace snake
