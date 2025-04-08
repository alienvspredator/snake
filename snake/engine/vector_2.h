//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include <ostream>

namespace engine {

class Vector2 {
 public:
  float x_, y_;

  Vector2();
  Vector2(float x, float y);

  [[nodiscard]] float Magnitude() const;
  [[nodiscard]] float SqrMagnitude() const;
  [[nodiscard]] float Distance(const Vector2& v) const;
  [[nodiscard]] float SqrDistance(const Vector2& v) const;

  Vector2& operator=(const Vector2& v) {
    x_ = v.x_, y_ = v.y_;
    return *this;
  }

  Vector2& operator=(const float& f) {
    x_ = y_ = f;
    return *this;
  }

  Vector2& operator-() {
    x_ = -x_, y_ = -y_;
    return *this;
  }

  bool operator==(const Vector2& v) const {
    return (x_ == v.x_) && (y_ == v.y_);
  }

  bool operator!=(const Vector2& v) const {
    return (x_ != v.x_) || (y_ != v.y_);
  }

  //VECTOR2 TO VECTOR2
  Vector2 operator+(const Vector2& v) const { return {x_ + v.x_, y_ + v.y_}; }

  Vector2 operator-(const Vector2& v) const { return {x_ - v.x_, y_ - v.y_}; }

  Vector2 operator*(const Vector2& v) const { return {x_ * v.x_, y_ * v.y_}; }

  Vector2 operator/(const Vector2& v) const { return {x_ / v.x_, y_ / v.y_}; }

  //VECTOR2 TO THIS
  Vector2& operator+=(const Vector2& v) {
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }

  Vector2& operator-=(const Vector2& v) {
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  Vector2& operator*=(const Vector2& v) {
    x_ *= v.x_;
    y_ *= v.y_;
    return *this;
  }

  Vector2& operator/=(const Vector2& v) {
    x_ /= v.x_;
    y_ /= v.y_;
    return *this;
  }

  // Scalar TO Vector2
  Vector2 operator+(const float v) const { return {x_ + v, y_ + v}; }

  Vector2 operator-(const float v) const { return {x_ - v, y_ - v}; }

  Vector2 operator*(const float v) const { return {x_ * v, y_ * v}; }

  Vector2 operator/(const float v) const { return {x_ / v, y_ / v}; }

  //SCALAR TO THIS
  Vector2& operator+=(const float v) {
    x_ += v;
    y_ += v;
    return *this;
  }

  Vector2& operator-=(const float v) {
    x_ -= v;
    y_ -= v;
    return *this;
  }

  Vector2& operator*=(const float v) {
    x_ *= v;
    y_ *= v;
    return *this;
  }

  Vector2& operator/=(const float v) {
    x_ /= v;
    y_ /= v;
    return *this;
  }

  // Stream to this
  friend std::ostream& operator<<(std::ostream& stream, const Vector2& v) {
    return stream << "(" << v.x_ << "," << v.y_ << ")";
  }
};

}  // namespace engine
