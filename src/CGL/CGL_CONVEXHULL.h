#ifndef CGL_CONVEXHULL_H
#define CGL_CONVEXHULL_H

#include "CGL_UTILS.h"

typedef struct cgl_convexhull {
  unsigned int* points;
  unsigned int count;
} CGL_Convexhull_t;

void CGL_CONVEXHULL_FREE(CGL_Convexhull_t* hull);
CGL_Convexhull_t CGL_CONVEXHULL_JARVIS(CGL_Point_t* points, const unsigned int count);
CGL_Convexhull_t CGL_CONVEXHULL_CHAN(CGL_Point_t* points, const unsigned int count);

#endif /* CGL_CONVEXHULL_H */
