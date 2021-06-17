#include "VLL_UTILS.h"

VLL_Color_t VLL_UTILS_GETCOLOR(VLL_Color_Preset_t preset) {
  VLL_Color_t c = {.r = 0, .g = 0, .b = 0};
  switch (preset) {
  case RED:
    c.r = 255;
    break;
  case GREEN:
    c.g = 255;
    break;
  case BLUE:
    c.b = 255;
    break;
  default:
    break;
  }

  return c;
}
