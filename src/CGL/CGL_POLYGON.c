#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include "CGL_POLYGON.h"
#include "CGL_CONVEXHULL.h"

void CGL_POLYGON_FREE(CGL_Polygon_t* polygon) {
  free(polygon->points);
}

void CGL_POLYGON_DIAGONALSFREE(CGL_Polydiagonals_t* diagonals) {
  free(diagonals->vertex1);
  free(diagonals->vertex2);
}

static CGL_Polygon_t _INVALID_POLYGON() {
  CGL_Polygon_t poly = {.count = 0, .points = (unsigned int*) 0};
  return poly;
}

static int backward_order_cmp(const void* a, const void* b) {
  float p1 = *(float*) a;
  float p2 = *(float*) b;

  return p2 > p1;
}

static int forward_order_nan_cmp(const void* a, const void* b) {
  float p1 = *(float*) a;
  float p2 = *(float*) b;

  if (isnan(p1))
    return 1;

  if (isnan(p2))
    return -1;

  return p2 < p1;
}

static int forward_order_two_way_cmp(const void* a, const void* b) {
  float p1x = *(float*) a;
  float p1y = *(((float*) a) + 1);
  float p2x = *(float*) b;
  float p2y = *(((float*) b) + 1);

  if (p1x == p2x) {
    return p2y < p1y;
  }
  else {
    return p2x < p1x;
  }
}

static CGL_Polygon_t _STAR_POLYGON_FROM_POINT(CGL_Point_t middle, CGL_Point_t* points, const unsigned int count) {
  if (sizeof(float) != sizeof(unsigned int))
    return _INVALID_POLYGON();

  CGL_Polygon_t result = {.count = count, .points = malloc(sizeof(unsigned int) * count)};

  void* data    = malloc((sizeof(float) + sizeof(unsigned int)) * count);
  float* values = data;
  int* indices  = data;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];
    p.x -= middle.x;
    p.y -= middle.y;
    values[2 * i]      = atan2f(p.y, p.x);
    indices[2 * i + 1] = i;
  }

  qsort(data, count, sizeof(float) + sizeof(unsigned int), backward_order_cmp);

  for (unsigned int i = 0; i < count; i++) {
    result.points[i] = indices[2 * i + 1];
  }

  free(data);

  return result;
}

CGL_Polygon_t CGL_POLYGON_QUICKSTAR(CGL_Point_t* points, const unsigned int count) {
  if (!points)
    return _INVALID_POLYGON();

  if (count <= 3) {
    CGL_Polygon_t result = {.count = count, .points = malloc(sizeof(unsigned int) * count)};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  float left   = FLT_MAX;
  float right  = -FLT_MAX;
  float top    = -FLT_MAX;
  float bottom = FLT_MAX;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];

    if (p.x < left)
      left = p.x;
    if (p.x > right)
      right = p.x;
    if (p.y < bottom)
      bottom = p.y;
    if (p.y > top)
      top = p.y;
  }

  CGL_Point_t middle = {.x = (left + right) / 2.0f, .y = (top + bottom) / 2.0f};

  return _STAR_POLYGON_FROM_POINT(middle, points, count);
}

CGL_Polygon_t CGL_POLYGON_UNIFORMQUICKSTAR(CGL_Point_t* points, const unsigned int count) {
  if (!points)
    return _INVALID_POLYGON();

  if (count <= 3) {
    CGL_Polygon_t result = {.count = count, .points = malloc(sizeof(unsigned int) * count)};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  CGL_Convexhull_t hull = CGL_CONVEXHULL_CHAN(points, count);

  float left   = FLT_MAX;
  float right  = -FLT_MAX;
  float top    = -FLT_MAX;
  float bottom = FLT_MAX;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];

    if (p.x < left)
      left = p.x;
    if (p.x > right)
      right = p.x;
    if (p.y < bottom)
      bottom = p.y;
    if (p.y > top)
      top = p.y;
  }

  int success = 0;
  CGL_Point_t middle;

  while (!success) {
    CGL_Point_t p = {
      .x = left + (((float) rand()) / RAND_MAX) * (right - left),
      .y = bottom + (((float) rand()) / RAND_MAX) * (top - bottom)};

    success = 1;

    for (unsigned int i = 0; i < hull.count - 1; i++) {
      CGL_Point_t a = points[hull.points[i]];
      CGL_Point_t b = points[hull.points[i + 1]];

      if (CGL_UTILS_ORIENTATION(a, b, p) == -1)
        success = 0;
    }

    CGL_Point_t a = points[hull.points[hull.count - 1]];
    CGL_Point_t b = points[hull.points[0]];
    if (CGL_UTILS_ORIENTATION(a, b, p) == -1)
      success = 0;

    middle = p;
  }

  CGL_CONVEXHULL_FREE(&hull);

  return _STAR_POLYGON_FROM_POINT(middle, points, count);
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

  unsigned int left  = 0;
  unsigned int right = 0;

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

  qsort(points_copy, count, sizeof(float) + sizeof(unsigned int), forward_order_nan_cmp);

  unsigned int result_ptr = lower_hull_count;

  for (unsigned int i = 0; i < count; i++) {
    if (isnan(values[2 * i]))
      break;
    result.points[result_ptr++] = indices[2 * i + 1];
  }

  free(points_copy);
  CGL_CONVEXHULL_FREE(&hull);

  return result;
}

CGL_Convexhull_t CGL_POLYGON_CONVEXHULL(CGL_Polygon_t* polygon, CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = (unsigned int*) 0, .count = 0};
  if (!points || !polygon || polygon->count != count)
    return err_result;

  if (count <= 3) {
    CGL_Convexhull_t result = {.points = malloc(sizeof(unsigned int) * count), .count = count};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  unsigned int* scratch      = malloc(sizeof(unsigned int) * 2 * (count + 1));
  unsigned int scratch_begin = count;
  unsigned int scratch_end   = count + 1;

  {
    CGL_Point_t v1 = points[polygon->points[0]];
    CGL_Point_t v2 = points[polygon->points[1]];
    CGL_Point_t v3 = points[polygon->points[2]];

    if (CGL_UTILS_ORIENTATION(v1, v2, v3) == 1) {
      scratch[scratch_end++] = polygon->points[0];
      scratch[scratch_end++] = polygon->points[1];
    }
    else {
      scratch[scratch_begin--] = polygon->points[1];
      scratch[scratch_begin--] = polygon->points[0];
    }

    scratch[scratch_begin--] = polygon->points[2];
    scratch[scratch_end++]   = polygon->points[2];
  }

  for (unsigned int i = 3; i < count; i++) {
    unsigned int index = polygon->points[i];
    CGL_Point_t p      = points[index];

    int condition1 = 1;
    int condition2 = 1;

    if (CGL_UTILS_ORIENTATION(p, points[scratch[scratch_begin + 1]], points[scratch[scratch_begin + 2]]) == 1)
      condition1 = 0;

    if (CGL_UTILS_ORIENTATION(points[scratch[scratch_end - 2]], points[scratch[scratch_end - 1]], p) == 1)
      condition2 = 0;

    if (!condition1 && !condition2)
      continue;

    while (condition1) {
      scratch_begin++;

      if (CGL_UTILS_ORIENTATION(p, points[scratch[scratch_begin + 1]], points[scratch[scratch_begin + 2]]) >= 0)
        condition1 = 0;
    }

    scratch[scratch_begin--] = index;

    while (condition2) {
      scratch_end--;

      if (CGL_UTILS_ORIENTATION(points[scratch[scratch_end - 2]], points[scratch[scratch_end - 1]], p) >= 0)
        condition2 = 0;
    }

    scratch[scratch_end++] = index;
  }

  const unsigned int hull_count = scratch_end - scratch_begin - 2;

  CGL_Convexhull_t result = {.points = malloc(sizeof(unsigned int) * hull_count), .count = hull_count};

  memcpy(result.points, scratch + scratch_begin + 1, sizeof(unsigned int) * hull_count);

  free(scratch);

  return result;
}

CGL_Polydiagonals_t CGL_POLYGON_MONTRIANGLE(CGL_Polygon_t* polygon, CGL_Point_t* points, const unsigned int count) {
  CGL_Polydiagonals_t err_result = {.vertex1 = (unsigned int*) 0, .vertex2 = (unsigned int*) 0, .count = 0};
  if (!points || !polygon || polygon->count != count || count <= 3)
    return err_result;

  unsigned int left  = 0;
  unsigned int right = 0;

  float left_val  = FLT_MAX;
  float right_val = -FLT_MAX;

  for (unsigned int i = 0; i < count; i++) {
    const unsigned int index = polygon->points[i];
    CGL_Point_t p            = points[index];

    if (p.x < left_val) {
      left_val = p.x;
      left     = i;
    }
    if (p.x > right_val) {
      right_val = p.x;
      right     = i;
    }
  }

  void* points_ordered = malloc(((2 * sizeof(float)) + (2 * sizeof(unsigned int))) * count);
  float* values        = points_ordered;
  int* indices         = points_ordered;

  for (unsigned int i = 0; i < count; i++) {
    values[4 * i]      = points[polygon->points[i]].x;
    values[4 * i + 1]  = points[polygon->points[i]].y;
    indices[4 * i + 2] = polygon->points[i];
    indices[4 * i + 3] = (left < right) ? (left < i && i < right) : (left > i || i < right);
  }

  qsort(points_ordered, count, (2 * sizeof(float)) + (2 * sizeof(unsigned int)), forward_order_two_way_cmp);

  CGL_Polydiagonals_t result = {
    .vertex1 = malloc(sizeof(unsigned int) * (count - 2)),
    .vertex2 = malloc(sizeof(unsigned int) * (count - 2)),
    .count   = 0};

  unsigned int result_ptr = 0;

  unsigned int* stack    = malloc(sizeof(unsigned int) * count);
  unsigned int stack_ptr = 0;

  stack[stack_ptr++] = 0;
  stack[stack_ptr++] = 1;

  for (unsigned int i = 2; i < count - 1; i++) {
    CGL_Point_t current_point;
    current_point.x      = values[4 * i];
    current_point.y      = values[4 * i + 1];
    unsigned int index_i = indices[4 * i + 2];
    int chain_i          = indices[4 * i + 3];
    int chain_top        = indices[4 * stack[stack_ptr - 1] + 3];

    if (chain_i != chain_top) {
      while (stack_ptr > 1) {
        unsigned int index = indices[4 * stack[stack_ptr - 1] + 2];

        result.vertex1[result_ptr] = index_i;
        result.vertex2[result_ptr] = index;

        result_ptr++;
        stack_ptr--;
      }
      stack_ptr--;
      stack[stack_ptr++] = i - 1;
      stack[stack_ptr++] = i;
    }
    else {
      CGL_Point_t previous_stack_point;
      previous_stack_point.x = values[4 * stack[stack_ptr - 1]];
      previous_stack_point.y = values[4 * stack[stack_ptr - 1] + 1];
      stack_ptr--;

      while (stack_ptr > 0) {
        CGL_Point_t current_stack_point;
        current_stack_point.x = values[4 * stack[stack_ptr - 1]];
        current_stack_point.y = values[4 * stack[stack_ptr - 1] + 1];

        int orient = CGL_UTILS_ORIENTATION(current_point, previous_stack_point, current_stack_point);

        if ((orient <= 0 && chain_i == 1) || (orient >= 0 && chain_i == 0))
          break;

        unsigned int index         = indices[4 * stack[stack_ptr - 1] + 2];
        result.vertex1[result_ptr] = index_i;
        result.vertex2[result_ptr] = index;

        previous_stack_point = current_stack_point;

        result_ptr++;
        stack_ptr--;
      }

      stack_ptr++;
      stack[stack_ptr++] = i;
    }
  }

  unsigned int index_n = indices[4 * (count - 1) + 2];
  stack_ptr--;

  while (stack_ptr > 1) {
    unsigned int index = indices[4 * stack[stack_ptr - 1] + 2];

    result.vertex1[result_ptr] = index_n;
    result.vertex2[result_ptr] = index;

    result_ptr++;
    stack_ptr--;
  }

  free(stack);
  free(points_ordered);

  result.count   = result_ptr;
  result.vertex1 = realloc(result.vertex1, sizeof(unsigned int) * result.count);
  result.vertex2 = realloc(result.vertex2, sizeof(unsigned int) * result.count);

  return result;
}
