//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include "../engine/vector_2.h"
#include "../config.h"

namespace snake {

enum class Direction { kUp, kDown, kLeft, kRight };

class Transform {
 public:
  struct CellPos {
    int x_, y_;

    CellPos(int x, int y) {
      x_ = x;
      y_ = y;
    }
  };

  engine::Vector2 position_;
  engine::Vector2 scale_;
  Direction direction_;

  Transform(const float xpos, const float ypos) {
    position_ = engine::Vector2(xpos, ypos);
    scale_ = engine::Vector2(1.0f, 1.0f);
    direction_ = Direction::kUp;
  }

  Transform() {
    position_ = engine::Vector2(0.0, 0.0);
    scale_ = engine::Vector2(1.0f, 1.0f);
    direction_ = Direction::kUp;
  }

  Transform(float xpos, const float ypos, const float xscl, const float yscl,
            const Direction facing) {
    position_ = engine::Vector2(xpos, ypos);
    scale_ = engine::Vector2(xscl, yscl);
    direction_ = facing;
  }

  [[nodiscard]] CellPos GetCellPos() const {
    return {static_cast<int>(position_.y_ / kCellSize),
                   static_cast<int>(position_.x_ / kCellSize)};
  }

  void Move() {
    switch (direction_) {
      case Direction::kUp:
        position_.y_ -= kCellSize * scale_.y_;
        break;
      case Direction::kDown:
        position_.y_ += kCellSize * scale_.y_;
        break;
      case Direction::kLeft:
        position_.x_ -= kCellSize * scale_.x_;
        break;
      case Direction::kRight:
        position_.x_ += kCellSize * scale_.x_;
        break;
      default:
        break;
    }
  }
};

}  // namespace snake
