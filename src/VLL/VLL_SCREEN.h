#ifndef VLL_SCREEN_H
#define VLL_SCREEN_H

#include <SDL2/SDL.h>
#include "VLL_CONTAINER.h"

struct vll_screen {
  SDL_Window* window;
  SDL_Renderer* renderer;
} typedef VLL_Screen_t;

void VLL_SCREEN_INIT(VLL_Screen_t* screen);
void VLL_SCREEN_DRAW(VLL_Screen_t* screen, VLL_Container_t* container);
void VLL_SCREEN_CLEAR(VLL_Screen_t* screen, VLL_Color_t color);
void VLL_SCREEN_UPDATE(VLL_Screen_t* screen);
/*
 * Blocks until the user requested exit
 */
void VLL_SCREEN_WAITFOREXIT(VLL_Screen_t* screen);
/*
 * Blocks until the user pressed the Y or N key
 * Returns 1 if the Y key was pressed
 */
int VLL_SCREEN_GETUSERVALIDATION(VLL_Screen_t* screen);
void VLL_SCREEN_DESTROY(VLL_Screen_t* screen);

#endif /* VLL_SCREEN_H */
