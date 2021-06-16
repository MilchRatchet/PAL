#include <SDL2/SDL.h>
#include "VLL_SCREEN.h"

void VLL_SCREEN_INIT(VLL_Screen* screen) {
  if (!screen)
    return;

  SDL_Init(SDL_INIT_VIDEO);
  screen->window =
    SDL_CreateWindow("VLL - Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

  screen->window_surface = SDL_GetWindowSurface(screen->window);

  Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  screen->surface = SDL_CreateRGBSurface(0, 1280, 720, 24, rmask, gmask, bmask, amask);
}

void VLL_SCREEN_DESTROY(VLL_Screen* screen) {
  if (!screen)
    return;

  SDL_DestroyWindow(screen->window);
  SDL_Quit();
}
