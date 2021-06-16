#ifndef VLL_CONTAINER_H
#define VLL_CONTAINER_H

#include "VLL_UTILS.h"

struct vll_container {
  VLL_Point* points;
  unsigned int points_count;
  unsigned int points_length;
  VLL_Line* lines;
  unsigned int lines_count;
  unsigned int lines_length;
} typedef VLL_CONTAINER;

void VLL_CONTAINER_INIT(VLL_CONTAINER* container);
void VLL_CONTAINER_ADDPOINT(VLL_CONTAINER* container, VLL_Point point);
void VLL_CONTAINER_ADDPOINTS(VLL_CONTAINER* container, VLL_Point* points, unsigned int points_count);
void VLL_CONTAINER_ADDLINE(VLL_CONTAINER* container, VLL_Line line);
void VLL_CONTAINER_ADDLINES(VLL_CONTAINER* container, VLL_Line* lines, unsigned int lines_count);
void VLL_CONTAINER_DESTROY(VLL_CONTAINER* container);

#endif /* VLL_CONTAINER_H */
