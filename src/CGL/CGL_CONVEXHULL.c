#include <stdlib.h>
#include <float.h>
#include "CGL_CONVEXHULL.h"
#include "CGL_UTILS.h"

void CGL_CONVEXFULL_FREE(CGL_Convexhull_t* hull) {
  free(hull->points);
}

/*
 * Jarvis march, convex hull algorithm
 * Time Complexity: O(nh)
 * Space Complexity: O(h)
 * where n = "number of points" and h = "number of points in convex hull"
 *
 * Takes a list of `count` many points.
 * Returns the list of indices of the points that lie on the convex hull in order.
 *
 * WARNING: May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_JARVIS(CGL_Point_t* points, unsigned int count) {
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

  if (first >= count)
    return err_result;

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
