#include <SDL2/SDL.h>
#include "VLL_SCREEN.h"
#include "VLL_CONTAINER.h"

void VLL_SCREEN_INIT(VLL_Screen_t* screen) {
  if (!screen)
    return;

  SDL_Init(SDL_INIT_VIDEO);
  screen->window =
    SDL_CreateWindow("VLL - Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, SDL_WINDOW_SHOWN);

  screen->renderer = SDL_CreateRenderer(screen->window, -1, 0);
}

/*
 * Preliminary, does not draw lines and points are rectangles
 */
void VLL_SCREEN_DRAW(VLL_Screen_t* screen, VLL_Container_t* container) {
  int width;
  int height;

  SDL_GetWindowSize(screen->window, &width, &height);

  for (unsigned int i = 0; i < container->points_count; i++) {
    VLL_Point_t point = container->points[i];

    const int x = point.x * width;
    const int y = (1.0f - point.y) * height;

    SDL_SetRenderDrawColor(screen->renderer, point.color.r, point.color.g, point.color.b, SDL_ALPHA_OPAQUE);
    VLL_RenderDrawCircle(screen->renderer, x, y, point.radius);
  }

  for (unsigned int i = 0; i < container->lines_count; i++) {
    VLL_Line_t line = container->lines[i];

    const int x1 = line.a.x * width;
    const int y1 = (1.0f - line.a.y) * height;
    const int x2 = line.b.x * width;
    const int y2 = (1.0f - line.b.y) * height;

    SDL_SetRenderDrawColor(screen->renderer, line.color.r, line.color.g, line.color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(screen->renderer, x1, y1, x2, y2);
  }
}

void VLL_SCREEN_CLEAR(VLL_Screen_t* screen, VLL_Color_t color) {
  SDL_SetRenderDrawColor(screen->renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(screen->renderer);
}

void VLL_SCREEN_UPDATE(VLL_Screen_t* screen) {
  SDL_RenderPresent(screen->renderer);
}

void VLL_SCREEN_WAITFOREXIT() {
  int exit = 0;

  while (!exit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        exit = 1;
      }
    }
  }
}

int VLL_SCREEN_GETUSERVALIDATION() {
  while (1) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_y) {
          return 1;
        }
        if (event.key.keysym.sym == SDLK_n) {
          return 0;
        }
      }
    }
  }
}

void VLL_SCREEN_DESTROY(VLL_Screen_t* screen) {
  if (!screen)
    return;

  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
  SDL_Quit();
}
