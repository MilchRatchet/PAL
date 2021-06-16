#ifndef VLL_UTILS_H
#define VLL_UTILS_H

#include <stdint.h>

struct vll_color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} typedef VLL_Color;

struct vll_point {
  float x;
  float y;
  float radius;
  VLL_Color color;
} typedef VLL_Point;

struct vll_line {
  VLL_Point a;
  VLL_Point b;
  float thickness;
  VLL_Color color;
} typedef VLL_Line;

#endif /* VLL_UTILS_H */
