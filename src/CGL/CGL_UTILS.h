#ifndef CGL_UTILS_H
#define CGL_UTILS_H

typedef struct cgl_point {
  float x;
  float y;
} CGL_Point_t;

/*!
 * \brief Point Orientation
 * \param a Vertex in Line
 * \param b Vertex in Line
 * \param p Vertex whose orientation is checked relative to line a-b
 * \return 1 if p is on the right side of a->b, 0 if points are collinear, -1 else.
 * \details May not be very robust. A better implementation is described in:
 *          Jonathan Richard Shewchuk, Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric
 *          Predicates, Discrete & Computational Geometry 18:305-363, 1997.
 */
int CGL_UTILS_ORIENTATION(CGL_Point_t a, CGL_Point_t b, CGL_Point_t p);

/*!
 * \brief Increment floating point number
 * \param a Number to increment
 * \return Smallest floating point number that is larger than a.
 */
float CGL_UTILS_INCF(float a);

#endif /* CGL_UTILS_H */
