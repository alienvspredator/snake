//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "collision.h"

#include "components/collider.h"
#include "components/segments.h"
#include "components/transform.h"
#include "events.h"

namespace snake {
void UpdateColliders(entt::registry& registry) {
  for (const auto view = registry.view<Collider, Transform>();
       const auto entity : view) {
    auto& col = view.get<Collider>(entity);
    const auto& tran = view.get<Transform>(entity);

    SDL_Rect rect;
    rect.x = static_cast<int>(tran.position_.x_);
    rect.y = static_cast<int>(tran.position_.y_);
    rect.w = static_cast<int>(kCellSize * tran.scale_.x_);
    rect.h = static_cast<int>(kCellSize * tran.scale_.y_);

    col.SetBounds(rect);
  }
}

void CheckPlayerCollisions(entt::registry& registry) {
  //get the snake head collider
  Collider* head_collider = nullptr;
  for (const auto head_view = registry.view<Head, Collider>();
       const auto entity : head_view) {
    head_collider = &head_view.get<Collider>(entity);
  }

  if (head_collider == nullptr)
    return;

  //check the head collider against all other valid colliders
  for (const auto view = registry.view<Collider>(); const auto entity : view) {
    auto col = view.get<Collider>(entity);

    //game over collision
    if (col.layer_ == ColliderLayer::kBody ||
        col.layer_ == ColliderLayer::kBoundary) {
      if (SDL_HasRectIntersection(&head_collider->bounds_, &col.bounds_)) {
        SendEvent(Event::kEndGame);
        break;
      }
    }
    //pickup collision
    else if (col.layer_ == ColliderLayer::kPickup) {
      if (SDL_HasRectIntersection(&head_collider->bounds_, &col.bounds_)) {
        SendEvent(Event::kPickup);
        break;
      }
    }
  }
}
}  // namespace snake