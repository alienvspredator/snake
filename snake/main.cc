#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "config.h"
#include "game.h"

constexpr int kSnakeFps = 30;

int main() {
  constexpr int frame_delay = 1000 / kSnakeFps;

  entt::registry registry;

  const auto game = new snake::Game();
  game->InitSDL("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                snake::kScreenWidth, snake::kScreenHeight, false);

  snake::Game::InitStartScreen(registry);

  while (game->Running()) {
    const auto frame_start = SDL_GetTicks();

    game->HandleEvents(registry);
    game->Update(registry);
    snake::Game::Render(registry);

    if (const auto frame_time = SDL_GetTicks() - frame_start;
        frame_delay > frame_time) {
      SDL_Delay(frame_delay - frame_time);
    }
  }

  snake::Game::CleanEntt(registry);
  game->CleanSDL();

  return 0;
}
