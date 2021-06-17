#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "TEST_CONVEXHULL.h"
#include "CGL_UTILS.h"
#include "CGL_CONVEXHULL.h"
#include "VLL_SCREEN.h"
#include "VLL_CONTAINER.h"
#include "VLL_UTILS.h"

void TEST_CONVEXHULL_JARVIS() {
  srand(clock());
  unsigned int count  = 10 + (rand() & 0xf);
  CGL_Point_t* points = malloc(sizeof(CGL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x = ((float) rand()) / RAND_MAX;
    const float y = ((float) rand()) / RAND_MAX;
    CGL_Point_t p = {.x = x, .y = y};

    points[i] = p;
  }

  CGL_Convexhull_t result = CGL_CONVEXHULL_JARVIS(points, count);

  printf("POINTS: %d HULL: %d\n", count, result.count);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  VLL_Point_t* vpoints = malloc(sizeof(VLL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p  = points[i];
    VLL_Point_t vp = {.x = p.x, .y = p.y, .radius = 5.0f, .color = VLL_UTILS_GETCOLOR(RED)};

    vpoints[i] = vp;
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index = result.points[i];

    vpoints[index].color = VLL_UTILS_GETCOLOR(BLUE);
  }

  VLL_CONTAINER_ADDPOINTS(&container, vpoints, count);

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  getchar();

  VLL_SCREEN_DESTROY(&screen);
}
