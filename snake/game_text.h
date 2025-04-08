//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include <entt/entt.hpp>

namespace snake {

void SetStartGameText(entt::registry& registry);
void SetGameOverText(entt::registry& registry);
void UpdateScoreText(entt::registry& registry);

}  // namespace snake
