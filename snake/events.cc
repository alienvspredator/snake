//
// Created by Danylo Shevchenko on 28.02.25.
//

#include "events.h"

namespace snake {
Uint32 kEventType = static_cast<Uint32>(-1);

void InitEvent() {
  kEventType = SDL_RegisterEvents(1);
}

void SendEvent(Event event) {
  if (kEventType != static_cast<Uint32>(-1)) {
    SDL_Event sdl_event;
    SDL_memset(&sdl_event, 0, sizeof(sdl_event));
    sdl_event.type = kEventType;
    sdl_event.user.code = static_cast<Sint32>(event);
    sdl_event.user.data1 = nullptr;
    sdl_event.user.data2 = nullptr;
    SDL_PushEvent(&sdl_event);
  }
}

}  // namespace snake
