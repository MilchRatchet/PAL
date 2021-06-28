#ifndef VLL_CONTAINER_H
#define VLL_CONTAINER_H

#include "VLL_UTILS.h"

typedef struct vll_container {
  VLL_Point_t* points;
  unsigned int points_count;
  unsigned int points_length;
  VLL_Line_t* lines;
  unsigned int lines_count;
  unsigned int lines_length;
} VLL_Container_t;

void VLL_CONTAINER_INIT(VLL_Container_t* container);
void VLL_CONTAINER_ADDPOINT(VLL_Container_t* container, VLL_Point_t point);
void VLL_CONTAINER_ADDPOINTS(VLL_Container_t* container, VLL_Point_t* points, unsigned int points_count);
void VLL_CONTAINER_ADDLINE(VLL_Container_t* container, VLL_Line_t line);
void VLL_CONTAINER_ADDLINES(VLL_Container_t* container, VLL_Line_t* lines, unsigned int lines_count);
void VLL_CONTAINER_DESTROY(VLL_Container_t* container);

#endif /* VLL_CONTAINER_H */
