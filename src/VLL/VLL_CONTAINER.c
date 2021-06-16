#include <stdlib.h>
#include <string.h>
#include "VLL_CONTAINER.h"

#define DEFAULT_POINT_COUNT 10
#define DEFAULT_LINE_COUNT 10

void VLL_CONTAINER_INIT(VLL_CONTAINER* container) {
  if (!container)
    return;

  container->points        = (VLL_Point*) malloc(sizeof(VLL_Point) * DEFAULT_POINT_COUNT);
  container->points_count  = 0;
  container->points_length = DEFAULT_POINT_COUNT;
  container->lines         = (VLL_Line*) malloc(sizeof(VLL_Line) * DEFAULT_LINE_COUNT);
  container->lines_count   = 0;
  container->lines_length  = DEFAULT_LINE_COUNT;
}

void VLL_CONTAINER_ADDPOINT(VLL_CONTAINER* container, VLL_Point point) {
  if (!container)
    return;

  if (container->points_count == container->points_length) {
    container->points_length *= 2;
    container->points = (VLL_Point*) realloc(container->points, sizeof(VLL_Point) * container->points_length);
  }

  container->points[container->points_count++] = point;
}

void VLL_CONTAINER_ADDPOINTS(VLL_CONTAINER* container, VLL_Point* points, unsigned int points_count) {
  if (!container || !points)
    return;

  if (container->points_count + points_count >= container->points_length) {
    container->points_length += points_count;
    container->points = (VLL_Point*) realloc(container->points, sizeof(VLL_Point) * container->points_length);
  }

  memcpy(container->points + container->points_count, points, sizeof(VLL_Point) * points_count);
  container->points_count += points_count;
}

void VLL_CONTAINER_ADDLINE(VLL_CONTAINER* container, VLL_Line line) {
  if (!container)
    return;

  if (container->lines_count == container->lines_length) {
    container->lines_length *= 2;
    container->lines = (VLL_Line*) realloc(container->lines, sizeof(VLL_Line) * container->lines_length);
  }

  container->lines[container->lines_count++] = line;
}

void VLL_CONTAINER_ADDLINES(VLL_CONTAINER* container, VLL_Line* lines, unsigned int lines_count) {
  if (!container || !lines)
    return;

  if (container->lines_count + lines_count >= container->lines_length) {
    container->lines_length += lines_count;
    container->lines = (VLL_Line*) realloc(container->lines, sizeof(VLL_Line) * container->lines_length);
  }

  memcpy(container->lines + container->lines_count, lines, sizeof(VLL_Line) * lines_count);
  container->lines_count += lines_count;
}

void VLL_CONTAINER_DESTROY(VLL_CONTAINER* container) {
  if (!container)
    return;

  free(container->points);
  free(container->lines);
}
