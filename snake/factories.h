//
// Created by Danylo Shevchenko on 27.02.25.
//

#pragma once

#include <entt/entt.hpp>

#include "SDL3/SDL_pixels.h"

namespace snake {

entt::entity MakeBoundary(entt::registry& registry, float xpos, float ypos,
                          float width, float height);

entt::entity MakePickup(entt::registry& registry);

entt::entity MakeStartGameText(entt::registry& registry, int pt_size,
                               SDL_Color color);

entt::entity MakeGameOverText(entt::registry& registry, int pt_size,
                              SDL_Color color);

entt::entity MakeScoreText(entt::registry& registry, int pt_size,
                           SDL_Color color);

entt::entity MakeSnakeHead(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale);

entt::entity MakeSnakeTail(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale);

entt::entity MakeSnakeBody(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale);

}  // namespace snake
