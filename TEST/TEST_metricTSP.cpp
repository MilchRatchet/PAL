#include "TEST_metricTSP.h"

#include <math.h>
#include <time.h>

#include "TEST_UTILS.h"

#include "VLL_CONTAINER.h"
#include "VLL_SCREEN.h"
#include "VLL_UTILS.h"

#include "AAL_metricTSP.h"

float distance(const unsigned int i, const unsigned int j, const void* metricSpaceIn) {
  float* metricSpace = (float*) metricSpaceIn;
  return sqrt(
    (metricSpace[2 * i] - metricSpace[2 * j]) * (metricSpace[2 * i] - metricSpace[2 * j])
    + (metricSpace[2 * i + 1] - metricSpace[2 * j + 1]) * (metricSpace[2 * i + 1] - metricSpace[2 * j + 1]));
}

void TEST_METRIC_TSP_NEAREST_ADDITION() {
  TEST_PRINT_INPROGRESS((char*)"AAL metric TSP nearest addition");

  srand(clock());
  unsigned int count = 10 + (rand() & 0x8f);
  float* points      = (float*) malloc(sizeof(float) * 2 * count);

  for (unsigned int i = 0; i < count; i++) {
    const float x     = ((float) rand()) / RAND_MAX;
    const float y     = ((float) rand()) / RAND_MAX;
    points[2 * i]     = x;
    points[2 * i + 1] = y;
  }

  AAL_metricTSP_instance instance = {count, points, distance};
  AAL_metricTSP_result result     = AAL_metricTSP_nearest_addition(instance);

  VLL_Screen_t screen;
  VLL_SCREEN_INIT(&screen);
  VLL_SCREEN_CLEAR(&screen, VLL_UTILS_COLOR(0x191919));

  VLL_Container_t container;
  VLL_CONTAINER_INIT(&container);

  for (unsigned int i = 0; i < count; i++) {
    VLL_CONTAINER_ADDPOINT(
      &container, VLL_UTILS_GETPOINT(points[2 * i], points[2 * i + 1], 4, VLL_UTILS_COLOR(0xdb4437)));
  }

  for (unsigned int i = 0; i < result.numberOfVertices; i++) {
    unsigned int index  = result.permutation[i];
    unsigned int index2 = (i == result.numberOfVertices - 1) ? result.permutation[0] : result.permutation[i + 1];

    VLL_CONTAINER_ADDLINE(
      &container, VLL_UTILS_GETLINE(container.points[index], container.points[index2], VLL_UTILS_COLOR(0xffffff)));
  }

  VLL_SCREEN_DRAW(&screen, &container);

  VLL_SCREEN_UPDATE(&screen);

  int success = VLL_SCREEN_GETUSERVALIDATION();

  TEST_PRINT_RESULT(success, (char*)"AAL metricTSP nearest addition");

  VLL_SCREEN_DESTROY(&screen);
  VLL_CONTAINER_DESTROY(&container);
  free(points);
  free(result.permutation);
}
