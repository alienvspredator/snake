//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

namespace snake {
void ProcessInput(entt::registry& registry, const SDL_Event& event);
bool UpdateSnake(entt::registry& registry);
void MoveSnake(entt::registry& registry);
void DestroySnake(entt::registry& registry);
}  // namespace snake
