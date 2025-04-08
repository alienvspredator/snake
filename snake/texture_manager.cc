//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "texture_manager.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>
#include "config.h"
#include "game.h"

namespace snake {
void TextureManager::SetDrawColour(engine::Colour colour) {
  SDL_SetRenderDrawColor(Game::renderer_, colour.r_, colour.g_, colour.b_,
                         colour.a_);
}

SDL_Texture* TextureManager::LoadTexture(const std::string& texture_path) {
  SDL_Surface* surface = IMG_Load(texture_path.c_str());
  const auto texture = SDL_CreateTextureFromSurface(Game::renderer_, surface);
  if (texture == nullptr) {
    spdlog::error("Failed to load texture: {}", SDL_GetError());
  }

  SDL_DestroySurface(surface);
  return texture;
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_Rect& src,
                          const SDL_Rect& dst) {
  SDL_FRect f_rect_src;
  SDL_FRect f_rect_dst;
  SDL_RectToFRect(&src, &f_rect_src);
  SDL_RectToFRect(&dst, &f_rect_dst);

  if (!SDL_RenderTexture(Game::renderer_, texture, &f_rect_src, &f_rect_dst))
    spdlog::error("Failed to draw texture: {}", SDL_GetError());
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_Rect& src,
                          const SDL_Rect& dst, const double rotation) {
  SDL_FRect f_rect_src;
  SDL_FRect f_rect_dst;
  SDL_RectToFRect(&src, &f_rect_src);
  SDL_RectToFRect(&dst, &f_rect_dst);

  if (!SDL_RenderTextureRotated(Game::renderer_, texture, &f_rect_src,
                                &f_rect_dst, rotation, nullptr, SDL_FLIP_NONE))
    spdlog::error("Failed to draw texture: {}", SDL_GetError());
}

void TextureManager::Draw(TTF_Font* font, const std::string& text,
                          SDL_Color color, int xoffset, int yoffset) {
  const auto surface = TTF_RenderText_Solid(font, text.c_str(), 0, color);
  const auto texture = SDL_CreateTextureFromSurface(Game::renderer_, surface);

  const auto props = SDL_GetTextureProperties(texture);
  const auto tex_w = static_cast<int>(
      SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0));
  const auto tex_h = static_cast<int>(
      SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0));

  const auto centre_x = (kScreenWidth - tex_w) / 2 + xoffset;
  const auto centre_y = (kScreenWidth - tex_h) / 2 + yoffset;
  const SDL_FRect dst_rect = {
      static_cast<float>(centre_x), static_cast<float>(centre_y),
      static_cast<float>(tex_w), static_cast<float>(tex_h)};

  SDL_RenderTexture(Game::renderer_, texture, nullptr, &dst_rect);
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(texture);
}
}  // namespace snake