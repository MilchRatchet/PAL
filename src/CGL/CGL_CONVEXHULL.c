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
CGL_Convexhull_t CGL_CONVEXHULL_CHAN(CGL_Point_t* points, unsigned int count) {
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

  unsigned int m              = (unsigned int) sqrt(count);
  unsigned int number_of_sets = 1 + count / m;

  CGL_Convexhull_t* hulls = (CGL_Convexhull_t*) malloc(sizeof(CGL_Convexhull_t) * number_of_sets);

  int first          = 0;
  float lowest_value = points[0].y;

  for (unsigned int i = 0; i < number_of_sets; i++) {
    const int offset      = i * m;
    CGL_Convexhull_t hull = CGL_CONVEXHULL_JARVIS(points + offset, MIN(m, count - offset));
    for (unsigned int j = 0; j < hull.count; j++) {
      const int p   = offset + hull.points[j];
      const float y = points[p].y;

      if (y < lowest_value) {
        lowest_value = y;
        first        = p;
      }
    }
    hulls[i] = hull;
  }

  CGL_Convexhull_t result;
  result.count     = 1;
  result.points    = (unsigned int*) malloc(sizeof(unsigned int) * count);
  result.points[0] = first;

  CGL_Point_t start = points[first];
  int* candidates   = (int*) malloc(sizeof(int) * number_of_sets);

  // For each set we determine the best candidate to be the next point
  for (unsigned int i = 0; i < number_of_sets; i++) {
    const int offset            = i * m;
    CGL_Convexhull_t hull       = hulls[i];
    int candidate               = 0;
    int candidate_index         = offset + hull.points[0];
    CGL_Point_t candidate_point = points[candidate_index];
    for (unsigned int j = 1; j < hull.count; j++) {
      const int index = offset + hull.points[j];
      CGL_Point_t p   = points[index];
      if (CGL_UTILS_ORIENTATION(start, candidate_point, p) == -1 || candidate_index == first) {
        candidate       = j;
        candidate_index = index;
        candidate_point = p;
      }
    }

    candidates[i] = candidate;
  }

  int last            = -1;
  CGL_Point_t current = start;

  while (first != last) {
    last                     = hulls[0].points[candidates[0]];
    CGL_Point_t end          = points[last];
    int chosen_candidate_set = 0;

    // We iterate through the candidates and determine the actual next point
    for (unsigned int i = 1; i < number_of_sets; i++) {
      const int candidate_index = candidates[i];
      const int index           = i * m + hulls[i].points[candidate_index];
      CGL_Point_t next_point    = points[index];
      if (CGL_UTILS_ORIENTATION(current, end, next_point) == -1) {
        end                  = next_point;
        last                 = index;
        chosen_candidate_set = i;
      }
    }

    result.points[result.count++]    = last;
    current                          = end;
    candidates[chosen_candidate_set] = (candidates[chosen_candidate_set] + 1) % hulls[chosen_candidate_set].count;

    // Now we update the candidates
    for (unsigned int i = 0; i < number_of_sets; i++) {
      const int offset          = i * m;
      CGL_Convexhull_t hull     = hulls[i];
      int index                 = candidates[i];
      CGL_Point_t new_candidate = points[offset + hull.points[index]];

      for (unsigned int j = 1; j < hull.count; j++) {
        const int index_p = (index + j) % hull.count;

        CGL_Point_t p = points[offset + hull.points[index_p]];

        if (CGL_UTILS_ORIENTATION(current, new_candidate, p) == -1) {
          new_candidate = p;
          index         = index_p;
        }
        else {
          break;
        }
      }

      candidates[i] = index;
    }
  }

  free(candidates);
  for (unsigned int i = 0; i < number_of_sets; i++) {
    CGL_CONVEXHULL_FREE(&hulls[i]);
  }
  free(hulls);

  result.points = (unsigned int*) realloc(result.points, sizeof(unsigned int) * result.count);
  return result;
}
