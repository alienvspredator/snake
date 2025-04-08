//
// Created by Danylo Shevchenko on 28.02.25.
//

#pragma once
#include <SDL3/SDL.h>

namespace snake {

extern Uint32 kEventType;

enum class Event : Sint32 {
  kEndGame,
  kPickup,
};

void InitEvent();
void SendEvent(Event event);

}  // namespace snake
