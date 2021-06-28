#ifndef VLL_UTILS_H
#define VLL_UTILS_H

#include <stdint.h>
#include <SDL2/SDL.h>

typedef enum vll_color_preset {
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
} VLL_Color_Preset_t;

typedef struct vll_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} VLL_Color_t;

typedef struct vll_point {
  float x;
  float y;
  int radius;
  VLL_Color_t color;
} VLL_Point_t;

typedef struct vll_line {
  VLL_Point_t a;
  VLL_Point_t b;
  VLL_Color_t color;
} VLL_Line_t;

VLL_Color_t VLL_UTILS_GETCOLOR(VLL_Color_Preset_t preset);
VLL_Color_t VLL_UTILS_COLOR(const int code);
VLL_Point_t VLL_UTILS_GETPOINT(float x, float y, int radius, VLL_Color_t color);
VLL_Line_t VLL_UTILS_GETLINE(VLL_Point_t a, VLL_Point_t b, VLL_Color_t color);
void VLL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);

#endif /* VLL_UTILS_H */
