#include <math.h>
#include "CGL_UTILS.h"

/*
 * Returns 1 if `p` is on the right side of the line `a`->`b`, 0 if the points are collinear, -1 else
 *
 * For more robustness consider:
 *
 * Jonathan Richard Shewchuk, Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric Predicates,
 * Discrete & Computational Geometry 18:305-363, 1997.
 */
int CGL_UTILS_ORIENTATION(CGL_Point_t a, CGL_Point_t b, CGL_Point_t p) {
  const float v = ((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
  return (v < 0) ? 1 : ((v == 0) ? 0 : -1);
}
