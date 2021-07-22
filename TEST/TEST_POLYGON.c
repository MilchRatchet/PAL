#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "TEST_POLYGON.h"
#include "CGL_UTILS.h"
#include "CGL_POLYGON.h"
#include "VLL_SCREEN.h"
#include "VLL_CONTAINER.h"
#include "VLL_UTILS.h"
#include "TEST_UTILS.h"

void TEST_POLYGON_QUICKSTAR() {
  TEST_PRINT_INPROGRESS("CGL_POLYGON_QUICKSTAR");

  srand(clock());
  unsigned int count  = 10 + (rand() & 0xf);
  CGL_Point_t* points = malloc(sizeof(CGL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x = ((float) rand()) / RAND_MAX;
    const float y = ((float) rand()) / RAND_MAX;
    CGL_Point_t p = {.x = x, .y = y};

    points[i] = p;
  }

  CGL_Polygon_t result = CGL_POLYGON_QUICKSTAR(points, count);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);
  VLL_SCREEN_CLEAR(&screen, VLL_UTILS_COLOR(0x191919));

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];
    VLL_CONTAINER_ADDPOINT(&container, VLL_UTILS_GETPOINT(p.x, p.y, 4, VLL_UTILS_COLOR(0xdb4437)));
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index = result.points[i];

    container.points[index].color = VLL_UTILS_COLOR(0xffffff);
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index  = result.points[i];
    unsigned int index2 = (i == result.count - 1) ? result.points[0] : result.points[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0xffffff)));
  }

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  int success = VLL_SCREEN_GETUSERVALIDATION();

  TEST_PRINT_RESULT(success, "CGL_POLYGON_QUICKSTAR");

  VLL_SCREEN_DESTROY(&screen);
  VLL_CONTAINER_DESTROY(&container);
  CGL_POLYGON_FREE(&result);
  free(points);
}

void TEST_POLYGON_UNIFORMQUICKSTAR() {
  TEST_PRINT_INPROGRESS("CGL_POLYGON_UNIFORMQUICKSTAR");

  srand(clock());
  unsigned int count  = 10 + (rand() & 0xf);
  CGL_Point_t* points = malloc(sizeof(CGL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x = ((float) rand()) / RAND_MAX;
    const float y = ((float) rand()) / RAND_MAX;
    CGL_Point_t p = {.x = x, .y = y};

    points[i] = p;
  }

  CGL_Polygon_t result = CGL_POLYGON_UNIFORMQUICKSTAR(points, count);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);
  VLL_SCREEN_CLEAR(&screen, VLL_UTILS_COLOR(0x191919));

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];
    VLL_CONTAINER_ADDPOINT(&container, VLL_UTILS_GETPOINT(p.x, p.y, 4, VLL_UTILS_COLOR(0xdb4437)));
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index = result.points[i];

    container.points[index].color = VLL_UTILS_COLOR(0xffffff);
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index  = result.points[i];
    unsigned int index2 = (i == result.count - 1) ? result.points[0] : result.points[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0xffffff)));
  }

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  int success = VLL_SCREEN_GETUSERVALIDATION();

  TEST_PRINT_RESULT(success, "CGL_POLYGON_UNIFORMQUICKSTAR");

  VLL_SCREEN_DESTROY(&screen);
  VLL_CONTAINER_DESTROY(&container);
  CGL_POLYGON_FREE(&result);
  free(points);
}

void TEST_POLYGON_MONOTONE() {
  TEST_PRINT_INPROGRESS("CGL_POLYGON_MONOTONE");

  srand(clock());
  unsigned int count  = 10 + (rand() & 0xf);
  CGL_Point_t* points = malloc(sizeof(CGL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x = ((float) rand()) / RAND_MAX;
    const float y = ((float) rand()) / RAND_MAX;
    CGL_Point_t p = {.x = x, .y = y};

    points[i] = p;
  }

  CGL_Polygon_t result = CGL_POLYGON_MONOTONE(points, count);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);
  VLL_SCREEN_CLEAR(&screen, VLL_UTILS_COLOR(0x191919));

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];
    VLL_CONTAINER_ADDPOINT(&container, VLL_UTILS_GETPOINT(p.x, p.y, 4, VLL_UTILS_COLOR(0xdb4437)));
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index = result.points[i];

    container.points[index].color = VLL_UTILS_COLOR(0xffffff);
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index  = result.points[i];
    unsigned int index2 = (i == result.count - 1) ? result.points[0] : result.points[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0xffffff)));
  }

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  int success = VLL_SCREEN_GETUSERVALIDATION();

  TEST_PRINT_RESULT(success, "CGL_POLYGON_MONOTONE");

  VLL_SCREEN_DESTROY(&screen);
  VLL_CONTAINER_DESTROY(&container);
  CGL_POLYGON_FREE(&result);
  free(points);
}

void TEST_POLYGON_CONVEXHULL() {
  TEST_PRINT_INPROGRESS("CGL_POLYGON_CONVEXHULL");

  srand(clock());
  unsigned int count  = 10 + (rand() & 0xf);
  CGL_Point_t* points = malloc(sizeof(CGL_Point_t) * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x = ((float) rand()) / RAND_MAX;
    const float y = ((float) rand()) / RAND_MAX;
    CGL_Point_t p = {.x = x, .y = y};

    points[i] = p;
  }

  CGL_Polygon_t polygon = CGL_POLYGON_QUICKSTAR(points, count);

  CGL_Convexhull_t result = CGL_POLYGON_CONVEXHULL(&polygon, points, count);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);
  VLL_SCREEN_CLEAR(&screen, VLL_UTILS_COLOR(0x191919));

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];
    VLL_CONTAINER_ADDPOINT(&container, VLL_UTILS_GETPOINT(p.x, p.y, 4, VLL_UTILS_COLOR(0xdb4437)));
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index = result.points[i];

    container.points[index].color = VLL_UTILS_COLOR(0xffffff);
  }

  for (unsigned int i = 0; i < polygon.count; i++) {
    unsigned int index  = polygon.points[i];
    unsigned int index2 = (i == polygon.count - 1) ? polygon.points[0] : polygon.points[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0x555555)));
  }

  for (unsigned int i = 0; i < result.count; i++) {
    unsigned int index  = result.points[i];
    unsigned int index2 = (i == result.count - 1) ? result.points[0] : result.points[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0xffffff)));
  }

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  int success = VLL_SCREEN_GETUSERVALIDATION();

  TEST_PRINT_RESULT(success, "CGL_POLYGON_CONVEXHULL");

  VLL_SCREEN_DESTROY(&screen);
  VLL_CONTAINER_DESTROY(&container);
  CGL_POLYGON_FREE(&polygon);
  CGL_CONVEXHULL_FREE(&result);
  free(points);
}
