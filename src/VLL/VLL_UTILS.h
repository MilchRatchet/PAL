#ifndef VLL_UTILS_H
#define VLL_UTILS_H

#include <stdint.h>

enum vll_color_preset { RED, GREEN, BLUE } typedef VLL_Color_Preset_t;

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

#endif /* VLL_UTILS_H */
