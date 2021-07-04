#ifndef CGL_CONVEXHULL_H
#define CGL_CONVEXHULL_H

#include "CGL_UTILS.h"

typedef struct cgl_convexhull {
  unsigned int* points;
  unsigned int count;
} CGL_Convexhull_t;

void CGL_CONVEXHULL_FREE(CGL_Convexhull_t* hull);

/*!
 * \brief Convexhull: Jarvis march
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the convex hull in clockwise order.
 * \details Jarvis march, convex hull algorithm
 *          Time Complexity: O(nh)
 *          Space Complexity: O(h)
 *          where n = "number of points" and h = "number of points in convex hull"
 *
 * \warning May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_JARVIS(CGL_Point_t* points, const unsigned int count);

/*!
 * \brief Convexhull: Chan's Algorithm
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the convex hull in clockwise order.
 * \details Chan's Algorithm, convex hull algorithm
 *          Time Complexity: O(n log(h))
 *          Space Complexity: O(n)
 *          where n = "number of points" and h = "number of points in convex hull"
 *
 *          The algorithm has a time complexity of O(n log(h)). However, this is only achieved through
 *          restarting if we chose m < h. The idea is through careful try and error to find m >= h but m not much
 *          larger. However, in practice, it is pointless to restart hence we choose one m and go with it. This
 *          means that the time complexity is O(nh) here.
 *
 * \warning May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_CHAN(CGL_Point_t* points, const unsigned int count);

/*!
 * \brief Convexhull: Kirkpatrick-Seidel "Ultimate Planar Convex Hull" Algorithm
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the convex hull in clockwise order.
 * \details Kirkpatrick-Seidel Algorithm, "ultimate planar convex hull algorithm"
 *          Time Complexity: O(n log(h))
 *          Space Complexity: O(n)
 *          where n = "number of points" and h = "number of points in convex hull"
 *
 * \warning May fail when more than 2 points are collinear.
 */
CGL_Convexhull_t CGL_CONVEXHULL_ULTIMATE(CGL_Point_t* points, const unsigned int count);

#endif /* CGL_CONVEXHULL_H */
