//
// Created by Danylo Shevchenko on 27.02.25.
//

#pragma once
#include <SDL3/SDL.h>
#include <entt/entt.hpp>

namespace snake {

class Game {
 public:
  static void InitStartScreen(entt::registry& registry);
  void InitSDL(const char* title, int xpos, int ypos, int width, int height,
               bool fullscreen);
  static void InitEntt(entt::registry& registry);

  void HandleEvents(entt::registry& registry);
  void Update(entt::registry& registry) const;
  static void Render(entt::registry& registry);

  void CleanSDL() const;
  static void CleanEntt(entt::registry& registry);

  [[nodiscard]] bool Running() const { return is_running_; }

  [[nodiscard]] int FrameCount() const { return frame_counter_; }

  static SDL_Renderer* renderer_;

 private:
  bool is_running_{false};
  bool is_awaiting_restart_{true};
  int frame_counter_{0};
  SDL_Window* window_{nullptr};
  SDL_Event event_{};
};
}  // namespace snake
