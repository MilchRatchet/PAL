#ifndef VLL_SCREEN_H
#define VLL_SCREEN_H

#include <SDL2/SDL.h>

struct vll_screen {
  SDL_Window* window;
  SDL_Surface* window_surface;
  SDL_Surface* surface;
} typedef VLL_Screen;

void VLL_SCREEN_INIT(VLL_Screen* screen);
void VLL_SCREEN_DESTROY(VLL_Screen* screen);

#endif /* VLL_SCREEN_H */
