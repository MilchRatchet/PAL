#ifndef CGL_UTILS_H
#define CGL_UTILS_H

struct cgl_point {
  float x;
  float y;
} typedef CGL_Point_t;

int CGL_UTILS_ORIENTATION(CGL_Point_t a, CGL_Point_t b, CGL_Point_t p);

#endif /* CGL_UTILS_H */
