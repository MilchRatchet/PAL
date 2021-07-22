#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include "CGL_POLYGON.h"
#include "CGL_CONVEXHULL.h"

void CGL_POLYGON_FREE(CGL_Polygon_t* polygon) {
  free(polygon->points);
}

static CGL_Polygon_t _INVALID_POLYGON() {
  CGL_Polygon_t poly = {.count = 0, .points = (unsigned int*) 0};
  return poly;
}

CGL_Polygon_t CGL_POLYGON_QUICKSTAR(CGL_Point_t* points, const unsigned int count);

int point_cmp(const void* a, const void* b) {
  float p1 = *(float*) a;
  float p2 = *(float*) b;

  if (isnan(p1))
    return 1;

  if (isnan(p2))
    return -1;

  return p2 < p1;
}

CGL_Polygon_t CGL_POLYGON_MONOTONE(CGL_Point_t* points, const unsigned int count) {
  if (!points || sizeof(float) != sizeof(unsigned int))
    return _INVALID_POLYGON();

  CGL_Polygon_t result = {.count = count, .points = malloc(sizeof(unsigned int) * count)};

  if (count <= 3) {
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  CGL_Convexhull_t hull = CGL_CONVEXHULL_CHAN(points, count);

  unsigned int left  = -1;
  unsigned int right = -1;

  float left_val  = FLT_MAX;
  float right_val = -FLT_MAX;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];

    if (p.x < left_val) {
      left_val = p.x;
      left     = i;
    }
    if (p.x > right_val) {
      right_val = p.x;
      right     = i;
    }
  }

  unsigned int start_index = 0;
  unsigned int end_index   = 0;

  for (unsigned int i = 0; i < hull.count; i++) {
    unsigned int p = hull.points[i];

    if (p == right)
      start_index = i;

    if (p == left)
      end_index = i;
  }

  unsigned int lower_hull_count;

  if (start_index < end_index) {
    lower_hull_count = end_index - start_index + 1;
    memcpy(result.points, hull.points + start_index, sizeof(unsigned int) * lower_hull_count);
  }
  else {
    lower_hull_count = end_index + (hull.count - start_index) + 1;
    memcpy(result.points, hull.points + start_index, sizeof(unsigned int) * (hull.count - start_index));
    memcpy(result.points + (hull.count - start_index), hull.points, sizeof(unsigned int) * (end_index + 1));
  }

  void* points_copy = malloc((sizeof(float) + sizeof(unsigned int)) * count);
  float* values     = points_copy;
  int* indices      = points_copy;

  for (unsigned int i = 0; i < count; i++) {
    values[2 * i]      = points[i].x;
    indices[2 * i + 1] = i;
  }

  for (unsigned int i = 0; i < lower_hull_count; i++) {
    values[2 * result.points[i]] = NAN;
  }

  qsort(points_copy, count, sizeof(float) + sizeof(unsigned int), point_cmp);

  unsigned int result_ptr = lower_hull_count;

  for (unsigned int i = 0; i < count; i++) {
    if (isnan(values[2 * i]))
      break;
    result.points[result_ptr++] = indices[2 * i + 1];
  }

  free(points_copy);

  return result;
}

CGL_Convexhull_t CGL_POLYGON_CONVEXHULL(CGL_Polygon_t* polygon, CGL_Point_t* points, const unsigned int count);
