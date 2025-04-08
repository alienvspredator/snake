//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once

#include <entt/entt.hpp>

namespace snake {

void UpdateColliders(entt::registry& registry);
void CheckPlayerCollisions(entt::registry& registry);

}  // namespace snake
