//
// Created by Danylo Shevchenko on 06.04.25.
//

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include "../texture_manager.h"

namespace snake {
class StartGameMainText {};

class StartGameSubText {};

class GameOverMainText {};

class GameOverSubText {};

class ScoreText {};

class Text {
 public:
  Text(const std::string& font_path, int pt_size, const SDL_Color colour,
       const int xoffset, const int yoffset) {
    font_ = TTF_OpenFont(font_path.c_str(), static_cast<float>(pt_size));
    if (font_ == nullptr) {
      spdlog::error("TTF_OpenFont failed: {}", SDL_GetError());
    }

    colour_ = colour;
    xoffset_ = xoffset;
    yoffset_ = yoffset;

    SetText("");
  }

  void SetText(const std::string& text) { text_ = text; }

  void Render() const {
    if (!text_.empty()) {
      TextureManager::Draw(font_, text_, colour_, xoffset_, yoffset_);
    }
  }

  void Clean() const { TTF_CloseFont(font_); }

 private:
  TTF_Font* font_{};
  SDL_Color colour_{};
  std::string text_;
  int xoffset_;
  int yoffset_;
};
}  // namespace snake
