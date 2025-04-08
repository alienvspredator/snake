//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "colour.h"

namespace engine {
Colour::Colour() {
  r_ = 255;
  g_ = 255;
  b_ = 255;
  a_ = 255;
}

Colour::Colour(const uint8_t r, const uint8_t g, const uint8_t b) {
  r_ = r;
  g_ = g;
  b_ = b;
  a_ = 255;
}

Colour::Colour(const uint8_t r, const uint8_t g, const uint8_t b,
               const uint8_t a) {
  r_ = r;
  g_ = g;
  b_ = b;
  a_ = a;
}
}  // namespace engine