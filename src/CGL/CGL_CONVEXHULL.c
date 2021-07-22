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

/*
 * Jarvis march, convex hull algorithm
 * Time Complexity: O(nh)
 * Space Complexity: O(h)
 * where n = "number of points" and h = "number of points in convex hull"
 *
 * Takes a list of `count` many points.
 * Returns the list of indices of the points that lie on the convex hull in clockwise order.
 *
 * WARNING: May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_JARVIS(CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = (unsigned int*) 0, .count = 0};
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

/*
 * Chan's Algorithm, convex hull algorithm
 * Time Complexity: O(n log(h))
 * Space Complexity: O(n)
 * where n = "number of points" and h = "number of points in convex hull"
 *
 * Takes a list of `count` many points.
 * Returns the list of indices of the points that lie on the convex hull in clockwise order.
 *
 * The algorithm has a time complexity of O(n log(h)). However, this is only achieved through
 * restarting if we chose m < h. The idea is through careful try and error to find m >= h but m not much
 * larger. However, in practice, it is pointless to restart hence we choose one m and go with it. This
 * means that the time complexity is O(nh) here.
 *
 * WARNING: May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_CHAN(CGL_Point_t* points, const unsigned int count) {
  CGL_Convexhull_t err_result = {.points = (unsigned int*) 0, .count = 0};
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
