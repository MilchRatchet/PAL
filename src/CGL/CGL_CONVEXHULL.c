#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "CGL_CONVEXHULL.h"
#include "CGL_UTILS.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void CGL_CONVEXHULL_FREE(CGL_Convexhull_t* hull) {
  free(hull->points);
}

CGL_Convexhull_t CGL_CONVEXHULL_JARVIS(CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = 0, .count = -1};
  if (!points)
    return err_result;

  // Trivial Case
  if (count <= 3) {
    CGL_Convexhull_t result = {.points = malloc(sizeof(unsigned int) * count), .count = count};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  unsigned int* hull       = (unsigned int*) malloc(sizeof(unsigned int) * 10);
  unsigned int hull_count  = 0;
  unsigned int hull_length = 10;

  unsigned int first = -1;
  float min          = FLT_MAX;

  for (unsigned int i = 0; i < count; i++) {
    const float x = points[i].x;
    if (x < min) {
      min   = x;
      first = i;
    }
  }

  unsigned int point_on_hull = first;
  unsigned int last          = -1;
  int k                      = 0;

  while (last != first) {
    hull[k] = point_on_hull;
    hull_count++;
    if (hull_count == hull_length) {
      hull_length *= 2;
      hull = realloc(hull, sizeof(unsigned int) * hull_length);
    }

    last                 = 0;
    const CGL_Point_t p1 = points[hull[k]];
    CGL_Point_t p2       = points[last];

    for (unsigned int j = 0; j < count; j++) {
      if (last == point_on_hull) {
        last = j;
        p2   = points[last];
      }
      else {
        const CGL_Point_t p = points[j];

        if (CGL_UTILS_ORIENTATION(p1, p2, p) == -1) {
          last = j;
          p2   = points[last];
        }
      }
    }

    k++;

    point_on_hull = last;
  }

  CGL_Convexhull_t result = {.points = realloc(hull, sizeof(unsigned int) * hull_count), .count = hull_count};

  return result;
}

CGL_Convexhull_t CGL_CONVEXHULL_CHAN(CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = 0, .count = -1};
  if (!points)
    return err_result;

  // Trivial Case
  if (count <= 3) {
    CGL_Convexhull_t result = {.points = malloc(sizeof(unsigned int) * count), .count = count};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  unsigned int m              = sqrt(count);
  unsigned int number_of_sets = (count + m - 1) / m;

  CGL_Convexhull_t* hulls = (CGL_Convexhull_t*) malloc(sizeof(CGL_Convexhull_t) * number_of_sets);

  unsigned int first         = 0;
  unsigned int first_in_hull = 0;
  float lowest_value         = FLT_MAX;
  unsigned int first_hull    = 0;
  unsigned int max_hull_size = 0;

  for (unsigned int i = 0; i < number_of_sets; i++) {
    const unsigned int offset = i * m;

    CGL_Convexhull_t hull = CGL_CONVEXHULL_JARVIS(points + offset, MIN(m, count - offset));

    max_hull_size += hull.count;

    for (unsigned int j = 0; j < hull.count; j++) {
      const unsigned int p = offset + hull.points[j];
      const float y        = points[p].y;

      if (y < lowest_value) {
        lowest_value  = y;
        first         = p;
        first_in_hull = j;
        first_hull    = i;
      }
    }

    hulls[i] = hull;
  }

  CGL_Convexhull_t result;
  result.count  = 0;
  result.points = (unsigned int*) malloc(sizeof(unsigned int) * max_hull_size);

  unsigned int point_index         = first;
  unsigned int point_in_hull_index = first_in_hull;
  CGL_Point_t point_on_hull        = points[first];
  unsigned int hull_of_point       = first_hull;

  while (result.count < max_hull_size) {
    result.points[result.count++] = point_index;

    unsigned int chosen_index         = point_index;
    unsigned int chosen_in_hull_index = point_in_hull_index;
    CGL_Point_t chosen_point          = points[chosen_index];
    unsigned int chosen_hull          = hull_of_point;

    for (unsigned int i = 0; i < number_of_sets; i++) {
      const unsigned int offset = i * m;

      CGL_Convexhull_t hull = hulls[i];

      if (hull.count <= 4) {
        for (unsigned int j = 0; j < hull.count; j++) {
          const unsigned int index = offset + hull.points[j];
          const CGL_Point_t p      = points[index];
          if (CGL_UTILS_ORIENTATION(point_on_hull, chosen_point, p) == -1 || point_index == chosen_index) {
            chosen_index         = index;
            chosen_point         = p;
            chosen_in_hull_index = j;
            chosen_hull          = i;
          }
        }
      }
      else {
        unsigned int step_size = hull.count / 3;

        unsigned int local_optimal_hull_index = 0;
        unsigned int local_optimal_index      = offset + hull.points[local_optimal_hull_index];
        CGL_Point_t local_optimal_point       = points[local_optimal_index];

        if (i == hull_of_point) {
          local_optimal_hull_index = (point_in_hull_index + 1) % hull.count;
          local_optimal_index      = offset + hull.points[local_optimal_hull_index];
          local_optimal_point      = points[local_optimal_index];
        }
        else {
          for (int j = 1; j < 4; j++) {
            if (j * step_size >= hull.count)
              break;

            const unsigned int index = offset + hull.points[j * step_size];
            const CGL_Point_t p      = points[index];
            if (
              CGL_UTILS_ORIENTATION(point_on_hull, local_optimal_point, p) == -1
              || point_index == local_optimal_index) {
              local_optimal_hull_index = j * step_size;
              local_optimal_index      = index;
              local_optimal_point      = p;
            }
          }

          step_size = hull.count / 4;

          while (step_size) {
            unsigned int h1 = (local_optimal_hull_index + step_size) % hull.count;
            unsigned int h2 = local_optimal_hull_index;

            h2 += (h2 < step_size) ? hull.count : 0;
            h2 -= step_size;

            const unsigned int c1 = offset + hull.points[h1];
            const unsigned int c2 = offset + hull.points[h2];

            const CGL_Point_t p1 = points[c1];
            const CGL_Point_t p2 = points[c2];

            if (CGL_UTILS_ORIENTATION(point_on_hull, local_optimal_point, p1) == -1) {
              local_optimal_hull_index = h1;
              local_optimal_index      = c1;
              local_optimal_point      = p1;
            }

            if (CGL_UTILS_ORIENTATION(point_on_hull, local_optimal_point, p2) == -1) {
              local_optimal_hull_index = h2;
              local_optimal_index      = c2;
              local_optimal_point      = p2;
            }

            step_size = step_size >> 1;
          }
        }

        if (
          CGL_UTILS_ORIENTATION(point_on_hull, chosen_point, local_optimal_point) == -1
          || point_index == chosen_index) {
          chosen_index         = local_optimal_index;
          chosen_point         = local_optimal_point;
          chosen_in_hull_index = local_optimal_hull_index;
          chosen_hull          = i;
        }
      }
    }

    point_on_hull       = chosen_point;
    point_index         = chosen_index;
    point_in_hull_index = chosen_in_hull_index;
    hull_of_point       = chosen_hull;

    if (point_index == first)
      break;
  }

  for (unsigned int i = 0; i < number_of_sets; i++) {
    CGL_CONVEXHULL_FREE(&hulls[i]);
  }
  free(hulls);

  result.points = (unsigned int*) realloc(result.points, sizeof(unsigned int) * result.count);
  return result;
}

static void swap_uints(unsigned int* a, unsigned int* b) {
  unsigned int temp = *a;
  *a                = *b;
  *b                = temp;
}

static unsigned int ULTIMATE_PARTITION(
  unsigned int* indices, unsigned int left, unsigned int right, unsigned int pivot, CGL_Point_t* points,
  int direction) {
  unsigned int pivot_index = indices[pivot];
  float pivot_value        = (direction) ? points[pivot_index].y : points[pivot_index].x;
  swap_uints(indices + pivot, indices + right);
  unsigned int store_index = left;

  for (unsigned int i = left; i < right; i++) {
    const float value = (direction) ? points[indices[i]].y : points[indices[i]].x;
    if (value < pivot_value) {
      swap_uints(indices + store_index, indices + i);
      store_index++;
    }
  }
  swap_uints(indices + right, indices + store_index);
  return store_index;
}

/*
 * Returns the index that represents the median (for even number of points it is the point just below the median)
 * Changes indices list such that the median is in median position
 * Takes on average linear time
 * Direction 0 implies x, 1 implies y
 */
static unsigned int ULTIMATE_MEDIAN(
  unsigned int* indices, const unsigned int count, CGL_Point_t* points, const int direction) {
  const unsigned int target = count / 2;
  unsigned int left         = 0;
  unsigned int right        = count;

  while (1) {
    if (left == right)
      return indices[left];

    int pivot_index = left + (((float) rand()) / RAND_MAX) * (right - left);
    pivot_index     = ULTIMATE_PARTITION(indices, left, right, pivot_index, points, direction);

    if (target == pivot_index) {
      return indices[pivot_index];
    }
    else if (target < pivot_index) {
      right = pivot_index - 1;
    }
    else {
      left = pivot_index + 1;
    }
  }
}

struct ULTIMATE_CONNECT_INPUT {
  int left;
  int right;
  unsigned int* selection;
  CGL_Point_t* points;
  const unsigned int count;
} typedef ULTCON_INPUT_t;

struct ULTIMATE_CONNECT_OUTPUT {
  int left;
  int right;
} typedef ULTCON_OUTPUT_t;

static ULTCON_OUTPUT_t ULTIMATE_CONNECT(ULTCON_INPUT_t input) {
  unsigned int median_index = ULTIMATE_MEDIAN(input.selection, input.count, input.points, 0);
  float median              = input.points[median_index].x;
  if (~input.count & 0b1) {
    median = CGL_UTILS_INCF(median);
  }
}

CGL_Convexhull_t CGL_CONVEXHULL_ULTIMATE(CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = 0, .count = -1};
  if (!points)
    return err_result;

  // Trivial Case
  if (count <= 3) {
    CGL_Convexhull_t result = {.points = malloc(sizeof(unsigned int) * count), .count = count};
    for (unsigned int i = 0; i < count; i++) {
      result.points[i] = i;
    }
    return result;
  }

  unsigned int left  = 0;
  unsigned int right = 0;
  float most_left    = FLT_MAX;
  float most_right   = -FLT_MAX;
  CGL_Point_t left_point;
  CGL_Point_t right_point;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];

    if (p.x < most_left || (p.x == most_left && p.y > left_point.y)) {
      left       = i;
      most_left  = p.x;
      left_point = p;
    }
    else if (p.x > most_right || (p.x == most_right && p.y > right_point.y)) {
      right       = i;
      most_right  = p.x;
      right_point = p;
    }
  }

  unsigned int* top         = (unsigned int*) malloc(sizeof(unsigned int) * count);
  unsigned int* bottom      = (unsigned int*) malloc(sizeof(unsigned int) * count);
  unsigned int top_count    = 0;
  unsigned int bottom_count = 0;

  for (unsigned int i = 0; i < count; i++) {
    CGL_Point_t p = points[i];

    int orient = CGL_UTILS_ORIENTATION(left_point, right_point, p);

    if (orient >= 0) {
      bottom[bottom_count++] = i;
    }

    if (orient <= 0) {
      top[top_count++] = i;
    }
  }
}
