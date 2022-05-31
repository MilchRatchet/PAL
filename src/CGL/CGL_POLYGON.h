#ifndef CGL_POLYGON_H
#define CGL_POLYGON_H

#include "CGL_UTILS.h"
#include "CGL_CONVEXHULL.h"

typedef struct cgl_polygon {
  unsigned int* points;
  unsigned int count;
} CGL_Polygon_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Frees an instance of polygon.
 * \param polygon Polygon to be freed.
 */
void CGL_POLYGON_FREE(CGL_Polygon_t* polygon);

/*!
 * \brief Computes deterministically a star shaped polygon from a given point set.
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the polygon in clockwise order.
 * \details Quickstar Algorithm
 *          Time Complexity: O(n log n)
 *          Space Complexity: O(n)
 *          where n = "number of points"
 */
CGL_Polygon_t CGL_POLYGON_QUICKSTAR(CGL_Point_t* points, const unsigned int count);

/*!
 * \brief Computes uniformly random a star shaped polygon from a given point set.
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the polygon in clockwise order.
 * \details Quickstar Algorithm
 *          Time Complexity: O(n log n)
 *          Space Complexity: O(n)
 *          where n = "number of points"
 *
 * \warning Has a non zero probability of not terminating.
 */
CGL_Polygon_t CGL_POLYGON_UNIFORMQUICKSTAR(CGL_Point_t* points, const unsigned int count);

/*!
 * \brief Computes deterministically a y-monotone polygon from a given point set.
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the polygon in clockwise order.
 * \details y-monotone Polygonalization Algorithm
 *          Time Complexity: O(n log n)
 *          Space Complexity: O(n)
 *          where n = "number of points"
 */
CGL_Polygon_t CGL_POLYGON_MONOTONE(CGL_Point_t* points, const unsigned int count);

/*!
 * \brief Computes the convex hull from a given polygon whose indices are ordered clockwise.
 * \param points List of vertices
 * \param count Number of vertices
 * \return Indices of the vertices on the convex hull in clockwise order.
 * \details Polygon Convexhull Algorithm
 *          Time Complexity: O(n)
 *          Space Complexity: O(n)
 *          where n = "number of points"
 */
CGL_Convexhull_t CGL_POLYGON_CONVEXHULL(CGL_Polygon_t* polygon, CGL_Point_t* points, const unsigned int count);

#ifdef __cplusplus
}
#endif

#endif /* CGL_POLYGON_H */
