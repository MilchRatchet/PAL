#include <SDL2/SDL.h>
#include "VLL_SCREEN.h"
#include "VLL_CONTAINER.h"

void VLL_SCREEN_INIT(VLL_Screen_t* screen) {
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

/*
 * Preliminary, does not draw lines and points are rectangles
 */
void VLL_SCREEN_DRAW(VLL_Screen_t* screen, VLL_Container_t* container) {
  int width;
  int height;

  SDL_GetWindowSize(screen->window, &width, &height);

  SDL_Rect p;
  uint32_t c;

  for (unsigned int i = 0; i < container->points_count; i++) {
    VLL_Point_t point = container->points[i];

    p.w = ((int) (point.radius * 2.0)) + 1;
    p.h = p.w;
    p.x = point.x * width - p.w / 2;
    p.y = (1.0f - point.y) * height - p.w / 2;

    c = (point.color.r) | (point.color.g << 8) | (point.color.b << 16);

    SDL_FillRect(screen->surface, &p, c);
  }
}

void VLL_SCREEN_CLEAR(VLL_Screen_t* screen) {
  SDL_FillRect(screen->surface, NULL, 0x00000000);
}

void VLL_SCREEN_UPDATE(VLL_Screen_t* screen) {
  SDL_BlitSurface(screen->surface, 0, screen->window_surface, 0);
  SDL_UpdateWindowSurface(screen->window);
}

void VLL_SCREEN_DESTROY(VLL_Screen_t* screen) {
  if (!screen)
    return;

  SDL_DestroyWindow(screen->window);
  SDL_Quit();
}
