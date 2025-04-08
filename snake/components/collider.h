//
// Created by Danylo Shevchenko on 07.04.25.
//

#pragma once
#include <SDL3/SDL.h>

#include "../config.h"

namespace snake {
enum class ColliderLayer {
  kNone,
  kDefault,
  kHead,
  kBody,
  kBoundary,
  kPickup,
};

class Collider {
 public:
  ColliderLayer layer_;
  SDL_Rect bounds_;

  explicit Collider(const ColliderLayer layer) {
    layer_ = layer;
    bounds_.x = 0;
    bounds_.y = 0;
    bounds_.w = kCellSize;
    bounds_.h = kCellSize;
  }

  Collider(const ColliderLayer layer, const SDL_Rect& bounds) {
    layer_ = layer;
    SetBounds(bounds);
  }

  void SetBounds(const SDL_Rect& bounds) {
    bounds_.x = bounds.x;
    bounds_.y = bounds.y;
    bounds_.w = bounds.w;
    bounds_.h = bounds.h;
  }
};
}  // namespace snake
