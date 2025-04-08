//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include <cstdint>
#include <ostream>

namespace engine {

class Colour {
#define COL_OVERFLOW(i) (i / 255 != 0)
#define COL_CLAMP_HI(x, i) (COL_OVERFLOW(i) ? 255 : (x + i > 255) ? 255 : x + i)
#define COL_CLAMP_LO(x, i) (COL_OVERFLOW(i) ? 0 : (x - i < 0) ? 0 : x - i)
#define COL_CLAMP(x, i) (COL_CLAMP_HI(COL_CLAMP_LO(x, i), i))
#define COL_TIMES(x, f) (COL_CLAMP(x, (int)(x * f)))

 public:
  uint8_t r_, g_, b_, a_;

  Colour();
  Colour(uint8_t r, uint8_t g, uint8_t b);
  Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  static Colour White() { return {255, 255, 255}; }

  static Colour Black() { return {0, 0, 0}; }

  static Colour Gray() { return {127, 127, 127}; }

  static Colour Red() { return {255, 0, 0}; }

  static Colour Green() { return {0, 255, 0}; }

  static Colour Blue() { return {0, 0, 255}; }

  Colour& operator=(const Colour& c) = default;

  Colour& operator-() {
    r_ = 255 - r_;
    g_ = 255 - g_;
    b_ = 255 - b_;
    return *this;
  }

  bool operator==(const Colour& c) const {
    return (r_ == c.r_) && (g_ == c.g_) && (b_ == c.b_) && (a_ == c.a_);
  }

  bool operator!=(const Colour& c) const { return !(*this == c); }

  Colour operator+(const int i) const {
    return {static_cast<uint8_t>(COL_CLAMP_HI(r_, i)),
            static_cast<uint8_t>(COL_CLAMP_HI(g_, i)),
            static_cast<uint8_t>(COL_CLAMP_HI(b_, i)), a_};
  }

  Colour operator-(const int i) const {
    return {static_cast<uint8_t>(COL_CLAMP_LO(r_, i)),
            static_cast<uint8_t>(COL_CLAMP_LO(g_, i)),
            static_cast<uint8_t>(COL_CLAMP_LO(b_, i)), a_};
  }

  Colour operator*(const float f) const {
    return {static_cast<uint8_t>(COL_TIMES(r_, f)),
            static_cast<uint8_t>(COL_TIMES(g_, f)),
            static_cast<uint8_t>(COL_TIMES(b_, f)), a_};
  }

  //SCALAR TO THIS
  Colour& operator+=(const int i) {
    r_ = COL_CLAMP_HI(r_, i);
    g_ = COL_CLAMP_HI(g_, i);
    b_ = COL_CLAMP_HI(b_, i);
    return *this;
  }

  Colour& operator-=(const int i) {
    r_ = COL_CLAMP_LO(r_, i);
    g_ = COL_CLAMP_LO(g_, i);
    b_ = COL_CLAMP_LO(b_, i);
    return *this;
  }

  Colour& operator*=(const float f) {
    r_ = COL_TIMES(r_, f);
    g_ = COL_TIMES(g_, f);
    b_ = COL_TIMES(b_, f);
    return *this;
  }

  //STREAM TO THIS
  friend std::ostream& operator<<(std::ostream& stream, const Colour& c) {
    return stream << "(" << static_cast<int>(c.r_) << ","
                  << static_cast<int>(c.g_) << "," << static_cast<int>(c.b_)
                  << "," << static_cast<int>(c.a_) << ")";
  }
};

}  // namespace engine
