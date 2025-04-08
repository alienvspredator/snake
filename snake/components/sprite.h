//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include "../config.h"
#include "../texture_manager.h"
#include "transform.h"

namespace snake {
class Sprite {
 public:
  SDL_Texture* texture_;
  SDL_Rect src_rect_{};
  SDL_Rect dst_rect_{};
  Direction direction_;

  explicit Sprite(std::string texture_path) {
    spdlog::info("Loading sprite from {}", texture_path);

    src_rect_.x = src_rect_.y = 0;
    src_rect_.w = src_rect_.h = kCellSize;
    dst_rect_.x = dst_rect_.y = 0;
    dst_rect_.w = dst_rect_.h = kCellSize;

    direction_ = Direction::kUp;

    texture_ = TextureManager::LoadTexture(texture_path);
  }

  void Update(const Transform& transform) {
    dst_rect_.x = static_cast<int>(transform.position_.x_);
    dst_rect_.y = static_cast<int>(transform.position_.y_);

    dst_rect_.w = src_rect_.w * static_cast<int>(transform.scale_.x_);
    dst_rect_.h = src_rect_.h * static_cast<int>(transform.scale_.y_);

    direction_ = transform.direction_;
  }

  void Render() const {
    switch (direction_) {
      case Direction::kUp:
        TextureManager::Draw(texture_, src_rect_, dst_rect_);
        break;
      case Direction::kDown:
        TextureManager::Draw(texture_, src_rect_, dst_rect_, 180.0);
        break;
      case Direction::kLeft:
        TextureManager::Draw(texture_, src_rect_, dst_rect_, 270.0);
        break;
      case Direction::kRight:
        TextureManager::Draw(texture_, src_rect_, dst_rect_, 90.0);
        break;
      default:
        spdlog::warn("Failed to render sprite");
        break;
    }
  }

  void Clean() const { SDL_DestroyTexture(texture_); }
};
}  // namespace snake
