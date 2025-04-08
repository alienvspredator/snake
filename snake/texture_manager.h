//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "engine/colour.h"

namespace snake {
class TextureManager {
 public:
  static void SetDrawColour(engine::Colour colour);
  static SDL_Texture* LoadTexture(const std::string& texture_path);
  static void Draw(SDL_Texture* texture, const SDL_Rect& src,
                   const SDL_Rect& dst);
  static void Draw(SDL_Texture* texture, const SDL_Rect& src,
                   const SDL_Rect& dst, double rotation);
  static void Draw(TTF_Font* font, const std::string& text, SDL_Color color,
                   int xoffset, int yoffset);
};
}  // namespace snake
