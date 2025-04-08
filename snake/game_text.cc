//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "game_text.h"
#include "components/segments.h"
#include "components/text.h"

namespace snake {
void SetStartGameText(entt::registry& registry) {
  for (const auto main_text_view = registry.view<StartGameMainText, Text>();
       const auto e : main_text_view) {
    auto& text = main_text_view.get<Text>(e);
    text.SetText("Start");
  }

  for (const auto sub_text_view = registry.view<StartGameSubText, Text>();
       const auto e : sub_text_view) {
    auto& text = sub_text_view.get<Text>(e);
    text.SetText("press enter to start");
  }
}

void SetGameOverText(entt::registry& registry) {
  for (const auto main_text_view = registry.view<GameOverMainText, Text>();
       const auto e : main_text_view) {
    auto& text = main_text_view.get<Text>(e);
    text.SetText("Game Over");
  }

  for (const auto sub_text_view = registry.view<GameOverSubText, Text>();
       const auto e : sub_text_view) {
    auto& text = sub_text_view.get<Text>(e);
    text.SetText("press enter to restart");
  }
}

void UpdateScoreText(entt::registry& registry) {
  const auto score = registry.view<Body>().size();

  for (const auto view = registry.view<ScoreText, Text>();
       const auto e : view) {
    auto& text = view.get<Text>(e);
    text.SetText(std::to_string(score));
  }
}
}  // namespace snake
