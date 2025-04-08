// Created by Danylo Shevchenko on 27.02.25.
//

#include "game.h"
#include <spdlog/spdlog.h>
#include "collision.h"
#include "components/sprite.h"
#include "components/text.h"
#include "config.h"
#include "engine/colour.h"
#include "events.h"
#include "factories.h"
#include "game_text.h"
#include "pickup.h"
#include "snake.h"

namespace snake {

SDL_Renderer* Game::renderer_ = nullptr;

void Game::InitStartScreen(entt::registry& registry) {
  MakeStartGameText(registry, 40, {200, 0, 0, 255});
  SetStartGameText(registry);
}

void Game::InitSDL(const char* title, const int xpos, const int ypos,
                   const int width, const int height, const bool fullscreen) {
  SDL_WindowFlags flags = 0;
  if (fullscreen)
    flags |= SDL_WINDOW_FULLSCREEN;

  is_running_ = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
  if (is_running_) {
    spdlog::info("SDL subsystem is initialised");

    window_ = SDL_CreateWindow(title, width, height, flags);
    if (window_) {
      spdlog::info("Window created");
    }

    SDL_SetWindowPosition(window_, xpos, ypos);

    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (renderer_) {
      spdlog::info("Renderer created");
    }

    TTF_Init();
    InitEvent();
  }
}

void Game::InitEntt(entt::registry& registry) {
  // Top left to top right
  MakeBoundary(registry, -kCellSize, -kCellSize, kScreenWidth + 2 * kCellSize,
               kCellSize);
  // Bottom left to bottom right
  MakeBoundary(registry, -kCellSize, -kScreenHeight,
               kScreenWidth + 2 * kCellSize, kCellSize);
  // Top left to bottom left
  MakeBoundary(registry, -kCellSize, 0, kCellSize, kScreenHeight);
  // Top right to bottom right
  MakeBoundary(registry, kScreenWidth, 0, kCellSize, kScreenHeight);

  constexpr float centre_x = kScreenWidth / 2.0f - kCellSize / 2.0f;
  constexpr float centre_y = kScreenHeight / 2.0f;
  constexpr float scale = 1;

  MakeSnakeHead(registry, centre_x, centre_y, scale, scale);
  MakeSnakeTail(registry, centre_x, centre_y + kCellSize, scale, scale);

  MakePickup(registry);
  MovePickup(registry);

  MakeGameOverText(registry, 40, {200, 0, 0, 255});
  MakeScoreText(registry, 25, {240, 210, 0, 255});
  UpdateScoreText(registry);
}

void Game::HandleEvents(entt::registry& registry) {
  while (SDL_PollEvent(&event_)) {
    switch (event_.type) {
      case SDL_EVENT_QUIT:
        is_running_ = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (event_.key.key == SDLK_ESCAPE)
          is_running_ = false;
        if (is_awaiting_restart_) {
          if (event_.key.key == SDLK_RETURN) {
            is_awaiting_restart_ = false;
            CleanEntt(registry);
            InitEntt(registry);
          }
        } else {
          ProcessInput(registry, event_);
        }
        break;
      case SDL_EVENT_KEY_UP:
        ProcessInput(registry, event_);
      default:
        break;
    }

    if (!is_awaiting_restart_ && event_.type == kEventType) {
      switch (static_cast<Event>(event_.user.code)) {
        case Event::kEndGame:
          SetGameOverText(registry);
          DestroySnake(registry);
          is_awaiting_restart_ = true;
          break;
        case Event::kPickup:
          MakeSnakeBody(registry, -kCellSize, -kCellSize, 1.0f, 1.0f);
          MovePickup(registry);
          UpdateScoreText(registry);
        default:
          break;
      }
    }
  }
}

void Game::Update(entt::registry& registry) const {
  if (is_awaiting_restart_)
    return;

  if (UpdateSnake(registry))
    MoveSnake(registry);

  UpdateColliders(registry);
  CheckPlayerCollisions(registry);

  for (const auto view = registry.view<Sprite, Transform>();
       const auto entity : view) {
    view.get<Sprite>(entity).Update(view.get<Transform>(entity));
  }
}

void Game::Render(entt::registry& registry) {
  TextureManager::SetDrawColour(engine::Colour::Gray());
  SDL_RenderClear(renderer_);

  TextureManager::SetDrawColour(engine::Colour::Black());
  constexpr int w = kScreenWidth - 1;
  constexpr int h = kScreenHeight - 1;
  SDL_RenderLine(renderer_, 0, 0, w, 0);
  SDL_RenderLine(renderer_, 0, 0, 0, h);
  SDL_RenderLine(renderer_, w, h, w, 0);
  SDL_RenderLine(renderer_, w, h, 0, h);

  for (const auto spr_view = registry.view<Sprite>();
       const auto entity : spr_view) {
    spr_view.get<Sprite>(entity).Render();
  }

  for (const auto txt_view = registry.view<Text>();
       const auto entity : txt_view) {
    txt_view.get<Text>(entity).Render();
  }

  SDL_RenderPresent(renderer_);
}

void Game::CleanEntt(entt::registry& registry) {
  for (const auto spr_view = registry.view<Sprite>();
       const auto entity : spr_view) {
    spr_view.get<Sprite>(entity).Clean();
  }

  for (const auto txt_view = registry.view<Text>();
       const auto entity : txt_view) {
    txt_view.get<Text>(entity).Clean();
  }

  registry.clear();
  spdlog::info("EnTT cleaned");
}

void Game::CleanSDL() const {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);

  TTF_Quit();
  SDL_Quit();

  spdlog::info("SDL cleaned");
}

}  // namespace snake
