#ifndef VLL_SCREEN_H
#define VLL_SCREEN_H

struct vll_screen {
  void* window;
  void* window_surface;
  void* surface;
} typedef VLL_Screen;

void VLL_SCREEN_INIT(VLL_Screen* screen);
void VLL_SCREEN_DESTROY(VLL_Screen* screen);

#endif /* VLL_SCREEN_H */
