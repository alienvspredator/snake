//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "snake.h"

#include "components/segments.h"
#include "components/transform.h"
#include "config.h"

namespace snake {
void ProcessInput(entt::registry& registry, const SDL_Event& event) {
  bool was_changed = false;
  bool is_vertical = false;
  Direction direction = {};
  bool boost = false;

  for (const auto view = registry.view<Head, Transform>();
       const auto entity : view) {
    const auto [head, transform] = view.get<Head, Transform>(entity);
    direction = transform.direction_;
    is_vertical = direction == Direction::kUp || direction == Direction::kDown;
    boost = head.boost_;
  }

  switch (event.type) {
    case SDL_EVENT_KEY_UP:
      switch (event.key.key) {
        case SDLK_SPACE:
          boost = false;
          was_changed = true;
          break;
        default:
          break;
      }
      break;
    case SDL_EVENT_KEY_DOWN:
      switch (event.key.key) {
        case SDLK_W:
        case SDLK_UP:
          if (!is_vertical) {
            direction = Direction::kUp;
            was_changed = true;
          }
          break;
        case SDLK_S:
        case SDLK_DOWN:
          if (!is_vertical) {
            direction = Direction::kDown;
            was_changed = true;
          }
          break;
        case SDLK_A:
        case SDLK_LEFT:
          if (is_vertical) {
            direction = Direction::kLeft;
            was_changed = true;
          }
          break;
        case SDLK_D:
        case SDLK_RIGHT:
          if (is_vertical) {
            direction = Direction::kRight;
            was_changed = true;
          }
          break;
        case SDLK_SPACE:
          boost = true;
          was_changed = true;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

  if (was_changed) {
    for (const auto view = registry.view<Head, Transform>();
         const auto entity : view) {
      view.get<Head>(entity).queued_dir_ = direction;
      view.get<Head>(entity).boost_ = boost;
      view.get<Head>(entity).ForceUpdate();
    }
  }
}

bool UpdateSnake(entt::registry& registry) {
  for (const auto view = registry.view<Head>(); const auto entity : view) {
    return view.get<Head>(entity).Update();
  }

  return false;
}

void MoveSnake(entt::registry& registry) {
  auto next_pos = engine::Vector2();
  auto next_dir = Direction::kUp;

  for (const auto head_view = registry.view<Head, Transform>();
       const auto entity : head_view) {
    auto& head = head_view.get<Transform>(entity);
    head.direction_ = head_view.get<Head>(entity).queued_dir_;

    next_pos = head.position_;
    next_dir = head.direction_;

    switch (head.direction_) {
      case Direction::kUp:
        head.position_.y_ -= kCellSize * head.scale_.y_;
        break;
      case Direction::kDown:
        head.position_.y_ += kCellSize * head.scale_.y_;
        break;
      case Direction::kLeft:
        head.position_.x_ -= kCellSize * head.scale_.x_;
        break;
      case Direction::kRight:
        head.position_.x_ += kCellSize * head.scale_.x_;
        break;
      default:
        break;
    }
  }

  for (const auto body_view = registry.view<Body, Transform>();
       const auto entity : body_view) {
    auto& body = body_view.get<Transform>(entity);

    const auto pos = body.position_;
    const auto dir = body.direction_;

    body.position_ = next_pos;
    body.direction_ = next_dir;

    next_pos = pos;
    next_dir = dir;
  }

  for (const auto tail_view = registry.view<Tail, Transform>();
       const auto entity : tail_view) {
    auto& tail = tail_view.get<Transform>(entity);
    tail.position_ = next_pos;
    tail.direction_ = next_dir;
  }
}

void DestroySnake(entt::registry& registry) {
  registry.reset(entt::type_index<Head>::value());
  registry.reset(entt::type_index<Body>::value());
  registry.reset(entt::type_index<Tail>::value());
}
}  // namespace snake
