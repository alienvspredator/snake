//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "vector_2.h"

namespace engine {
Vector2::Vector2() {
  x_ = y_ = 0;
}

Vector2::Vector2(float x, float y) {
  x_ = x;
  y_ = y;
}

float Vector2::Magnitude() const {
  return sqrt(SqrMagnitude());
}

float Vector2::SqrMagnitude() const {
  return x_ * x_ + y_ * y_;
}

float Vector2::Distance(const Vector2& v) const {
  return (v - *this).Magnitude();
}

float Vector2::SqrDistance(const Vector2& v) const {
  return (v - *this).SqrMagnitude();
}
}  // namespace engine