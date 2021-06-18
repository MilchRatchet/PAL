#ifndef VLL_UTILS_H
#define VLL_UTILS_H

#include <stdint.h>
#include <SDL2/SDL.h>

enum vll_color_preset {
  VLL_RED,
  VLL_GREEN,
  VLL_BLUE,
  VLL_YELLOW,
  VLL_PINK,
  VLL_ORANGE,
  VLL_GREY,
  VLL_BLACK,
  VLL_WHITE,
  VLL_GOLD,
  VLL_PURPLE
} typedef VLL_Color_Preset_t;

struct vll_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} typedef VLL_Color_t;

struct vll_point {
  float x;
  float y;
  float radius;
  VLL_Color_t color;
} typedef VLL_Point_t;

struct vll_line {
  VLL_Point_t a;
  VLL_Point_t b;
  float thickness;
  VLL_Color_t color;
} typedef VLL_Line_t;

VLL_Color_t VLL_UTILS_GETCOLOR(VLL_Color_Preset_t preset);
VLL_Color_t VLL_UTILS_COLOR(const int code);
void VLL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, float radius);

#endif /* VLL_UTILS_H */
