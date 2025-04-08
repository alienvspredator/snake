//
// Created by Danylo Shevchenko on 27.02.25.
//

#include "factories.h"
#include <SDL3/SDL.h>
#include "components/collider.h"
#include "components/pickup.h"
#include "components/segments.h"
#include "components/sprite.h"
#include "components/text.h"
#include "components/transform.h"
#ifdef MACOS_APP_BUNDLE
#include "CF/Resource.h"
#endif  // MACOS_APP_BUNDLE

namespace snake {
inline std::string GetAssetURL(const std::string& asset) {
#ifdef MACOS_APP_BUNDLE
  return CF::Resource::CopyURL(asset);
#else
  return asset;
#endif  // MACOS_APP_BUNDLE
}

entt::entity MakeBoundary(entt::registry& registry, const float xpos,
                          const float ypos, const float width,
                          const float height)

{
  const entt::entity e = registry.create();
  SDL_Rect rect;
  rect.x = static_cast<int>(xpos);
  rect.y = static_cast<int>(ypos);
  rect.w = static_cast<int>(width);
  rect.h = static_cast<int>(height);
  registry.emplace<Collider>(e, ColliderLayer::kBoundary, rect);
  return e;
}

entt::entity MakePickup(entt::registry& registry) {
  const entt::entity e = registry.create();
  registry.emplace<Pickup>(e);

  const auto url = GetAssetURL("assets/pickup.png");
  registry.emplace<Sprite>(e, url);
  registry.emplace<Transform>(e);
  registry.emplace<Collider>(e, ColliderLayer::kPickup);
  return e;
}

entt::entity MakeStartGameText(entt::registry& registry, int pt_size,
                               SDL_Color color) {
  const entt::entity e1 = registry.create();
  registry.emplace<StartGameMainText>(e1);

  const auto url = GetAssetURL("assets/open_sans.ttf");
  registry.emplace<Text>(e1, url, pt_size, color, 0, 0);

  const entt::entity e2 = registry.create();
  registry.emplace<StartGameSubText>(e2);
  registry.emplace<Text>(e2, url, 2 * pt_size / 3, color, 0, 50);

  return e1;
}

entt::entity MakeGameOverText(entt::registry& registry, int pt_size,
                              SDL_Color color) {
  const entt::entity e1 = registry.create();
  registry.emplace<GameOverMainText>(e1);

  const auto url = GetAssetURL("assets/open_sans.ttf");
  registry.emplace<Text>(e1, url, pt_size, color, 0, 0);

  const entt::entity e2 = registry.create();
  registry.emplace<GameOverSubText>(e2);
  registry.emplace<Text>(e2, url, (2 * pt_size) / 3, color, 0, 50);

  return e1;
}

entt::entity MakeScoreText(entt::registry& registry, int pt_size,
                           SDL_Color color) {
  const entt::entity e = registry.create();
  registry.emplace<ScoreText>(e);

  const auto url = GetAssetURL("assets/open_sans.ttf");
  registry.emplace<Text>(e, url, pt_size, color, -kScreenWidth / 2 + 24,
                         -kScreenHeight / 2 + 24);
  return e;
}

entt::entity MakeSnakeHead(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale) {
  const entt::entity e = registry.create();
  registry.emplace<Head>(e);
  registry.emplace<Part>(e);

  const auto url = GetAssetURL("assets/snake_head.png");
  registry.emplace<Sprite>(e, url);
  registry.emplace<Transform>(e, xpos, ypos, xscale, yscale, Direction::kUp);
  registry.emplace<Collider>(e, ColliderLayer::kHead);
  return e;
}

entt::entity MakeSnakeTail(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale) {
  const entt::entity e = registry.create();
  registry.emplace<Tail>(e);
  registry.emplace<Part>(e);

  const auto url = GetAssetURL("assets/snake_tail.png");
  registry.emplace<Sprite>(e, url);
  registry.emplace<Transform>(e, xpos, ypos, xscale, yscale, Direction::kUp);
  registry.emplace<Collider>(e, ColliderLayer::kBody);
  return e;
}

entt::entity MakeSnakeBody(entt::registry& registry, float xpos, float ypos,
                           float xscale, float yscale) {
  const entt::entity e = registry.create();
  registry.emplace<Body>(e);
  registry.emplace<Part>(e);

  const auto url = GetAssetURL("assets/snake_body.png");
  registry.emplace<Sprite>(e, url);
  registry.emplace<Transform>(e, xpos, ypos, xscale, yscale, Direction::kUp);
  registry.emplace<Collider>(e, ColliderLayer::kBody);
  return e;
}
}  // namespace snake
