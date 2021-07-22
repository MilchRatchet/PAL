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

void CGL_POLYGON_FREE(CGL_Polygon_t* polygon);
CGL_Polygon_t CGL_POLYGON_QUICKSTAR(CGL_Point_t* points, const unsigned int count);
CGL_Polygon_t CGL_POLYGON_UNIFORMQUICKSTAR(CGL_Point_t* points, const unsigned int count);
CGL_Polygon_t CGL_POLYGON_MONOTONE(CGL_Point_t* points, const unsigned int count);
CGL_Convexhull_t CGL_POLYGON_CONVEXHULL(CGL_Polygon_t* polygon, CGL_Point_t* points, const unsigned int count);

#ifdef __cplusplus
}
#endif

#endif /* CGL_POLYGON_H */
