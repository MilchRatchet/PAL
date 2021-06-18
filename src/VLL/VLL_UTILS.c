#include <SDL2/SDL.h>
#include "VLL_UTILS.h"

VLL_Color_t VLL_UTILS_GETCOLOR(VLL_Color_Preset_t preset) {
  VLL_Color_t c = {.r = 0, .g = 0, .b = 0};
  switch (preset) {
  case VLL_RED:
    c.r = 255;
    break;
  case VLL_GREEN:
    c.g = 255;
    break;
  case VLL_BLUE:
    c.b = 255;
    break;
  case VLL_YELLOW:
    c.r = 255;
    c.g = 255;
    break;
  case VLL_PINK:
    c.r = 255;
    c.g = 192;
    c.b = 203;
    break;
  case VLL_ORANGE:
    c.r = 255;
    c.g = 165;
    break;
  case VLL_GREY:
    c.r = 0x30;
    c.g = 0x30;
    c.b = 0x30;
    break;
  case VLL_BLACK:
    break;
  case VLL_WHITE:
    c.r = 255;
    c.g = 255;
    c.b = 255;
    break;
  case VLL_GOLD:
    c.r = 255;
    c.g = 215;
    break;
  case VLL_PURPLE:
    c.r = 255;
    c.b = 255;
    break;
  default:
    break;
  }

  return c;
}

/*
 * Returns a color where r=code[16-23], g=code[8-15] and b=code[0-7]
 */
VLL_Color_t VLL_UTILS_COLOR(const int code) {
  VLL_Color_t c = {.r = (code & 0xff0000) >> 16, .g = (code & 0x00ff00) >> 8, .b = code & 0x0000ff};
  return c;
}

void VLL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, float radius) {
  int head_x = radius - 1;
  int head_y = 0;
  int d_x    = 1;
  int d_y    = 1;
  int error  = (d_x - radius * 2);

  SDL_Point* points = malloc(sizeof(SDL_Point) * 8);
  SDL_Point p;

  while (head_x >= head_y) {
    p.x       = x + head_x;
    p.y       = y - head_y;
    points[0] = p;
    p.x       = x + head_x;
    p.y       = y + head_y;
    points[1] = p;
    p.x       = x - head_x;
    p.y       = y - head_y;
    points[2] = p;
    p.x       = x - head_x;
    p.y       = y + head_y;
    points[3] = p;
    p.x       = x + head_y;
    p.y       = y - head_x;
    points[4] = p;
    p.x       = x + head_y;
    p.y       = y + head_x;
    points[5] = p;
    p.x       = x - head_y;
    p.y       = y - head_x;
    points[6] = p;
    p.x       = x - head_y;
    p.y       = y + head_x;
    points[7] = p;

    SDL_RenderDrawPoints(renderer, points, 8);

    if (error <= 0) {
      head_y++;
      error += d_y;
      d_y += 2;
    }

    if (error > 0) {
      head_x--;
      d_x += 2;
      error += (d_x - 2 * radius);
    }
  }

  free(points);
}
