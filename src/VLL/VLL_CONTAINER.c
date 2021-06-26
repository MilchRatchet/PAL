#include <stdlib.h>
#include <string.h>
#include "VLL_CONTAINER.h"

#define DEFAULT_POINT_COUNT 10
#define DEFAULT_LINE_COUNT 10

void VLL_CONTAINER_INIT(VLL_Container_t* container) {
  if (!container)
    return;

  container->points        = (VLL_Point_t*) malloc(sizeof(VLL_Point_t) * DEFAULT_POINT_COUNT);
  container->points_count  = 0;
  container->points_length = DEFAULT_POINT_COUNT;
  container->lines         = (VLL_Line_t*) malloc(sizeof(VLL_Line_t) * DEFAULT_LINE_COUNT);
  container->lines_count   = 0;
  container->lines_length  = DEFAULT_LINE_COUNT;
}

void VLL_CONTAINER_ADDPOINT(VLL_Container_t* container, VLL_Point_t point) {
  if (!container)
    return;

  if (container->points_count == container->points_length) {
    container->points_length *= 2;
    container->points = (VLL_Point_t*) realloc(container->points, sizeof(VLL_Point_t) * container->points_length);
  }

  container->points[container->points_count++] = point;
}

void VLL_CONTAINER_ADDPOINTS(VLL_Container_t* container, VLL_Point_t* points, unsigned int points_count) {
  if (!container || !points)
    return;

  if (container->points_count + points_count >= container->points_length) {
    container->points_length += points_count;
    container->points = (VLL_Point_t*) realloc(container->points, sizeof(VLL_Point_t) * container->points_length);
  }

  memcpy(container->points + container->points_count, points, sizeof(VLL_Point_t) * points_count);
  container->points_count += points_count;
}

void VLL_CONTAINER_ADDLINE(VLL_Container_t* container, VLL_Line_t line) {
  if (!container)
    return;

  if (container->lines_count == container->lines_length) {
    container->lines_length *= 2;
    container->lines = (VLL_Line_t*) realloc(container->lines, sizeof(VLL_Line_t) * container->lines_length);
  }

  container->lines[container->lines_count++] = line;
}

void VLL_CONTAINER_ADDLINES(VLL_Container_t* container, VLL_Line_t* lines, unsigned int lines_count) {
  if (!container || !lines)
    return;

  if (container->lines_count + lines_count >= container->lines_length) {
    container->lines_length += lines_count;
    container->lines = (VLL_Line_t*) realloc(container->lines, sizeof(VLL_Line_t) * container->lines_length);
  }

  memcpy(container->lines + container->lines_count, lines, sizeof(VLL_Line_t) * lines_count);
  container->lines_count += lines_count;
}

void VLL_CONTAINER_DESTROY(VLL_Container_t* container) {
  if (!container)
    return;

  free(container->points);
  free(container->lines);
}
