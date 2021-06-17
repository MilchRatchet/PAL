#ifndef VLL_SCREEN_H
#define VLL_SCREEN_H

#include <SDL2/SDL.h>

struct vll_screen {
  SDL_Window* window;
  SDL_Surface* window_surface;
  SDL_Surface* surface;
} typedef VLL_Screen_t;

void VLL_SCREEN_INIT(VLL_Screen_t* screen);
void VLL_SCREEN_DESTROY(VLL_Screen_t* screen);

#endif /* VLL_SCREEN_H */
