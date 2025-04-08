//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "pickup.h"
#include <spdlog/spdlog.h>
#include <random>
#include "components/pickup.h"
#include "components/segments.h"
#include "components/transform.h"
#include "config.h"

namespace snake {
constexpr int kSnakeCellRows = kScreenHeight / kCellSize;
constexpr int kSnakeCellCols = kScreenWidth / kCellSize;

std::random_device rd;
std::mt19937 gen(rd());

#define CELL_IS_VALID(x, y) \
  ((x) >= 0 && (x) < kSnakeCellRows && (y) >= 0 && (y) < kSnakeCellCols)

void MovePickup(entt::registry& registry) {
  constexpr int kRows = kSnakeCellRows - 0;
  constexpr int kCols = kSnakeCellCols - 0;

  bool map[kRows][kCols];

  // Initialize all cells to valid
  for (auto& row : map) {
    for (bool& col : row) {
      col = true;
    }
  }

  // Remove current pickup location from valid cells
  const auto pickup_view = registry.view<Pickup, Transform>();
  for (const auto e : pickup_view) {
    if (const Transform::CellPos cell_pos =
            pickup_view.get<Transform>(e).GetCellPos();
        CELL_IS_VALID(cell_pos.x_, cell_pos.y_)) {
      map[cell_pos.x_][cell_pos.y_] = false;
    }
  }

  // Remove snake head from valid cells
  for (const auto snake_view = registry.view<Part, Transform>();
       const auto e : snake_view) {
    if (const Transform::CellPos cell_pos =
            snake_view.get<Transform>(e).GetCellPos();
        CELL_IS_VALID(cell_pos.x_, cell_pos.y_)) {
      map[cell_pos.x_][cell_pos.y_] = false;
    }
  }

  // Make list of all valid cells
  std::vector<Transform::CellPos> valid_cells;
  for (int row = 0; row < kRows; row++) {
    for (int col = 0; col < kCols; col++) {
      if (map[row][col]) {
        valid_cells.emplace_back(row, col);
      }
    }
  }

  // Randomly select a valid cell and move the pickup to that location
  std::uniform_int_distribution<std::mt19937::result_type> distrib(
      0, valid_cells.size() - 1);
  for (const auto e : pickup_view) {
    auto& trans = pickup_view.get<Transform>(e);
    const int rand_index = static_cast<int>(distrib(gen));

    const auto& rand_cell = valid_cells[rand_index];
    trans.position_.x_ = static_cast<float>(rand_cell.y_ * kCellSize);
    trans.position_.y_ = static_cast<float>(rand_cell.x_ * kCellSize);

    spdlog::info("Pickup moved");
  }
}

}  // namespace snake
