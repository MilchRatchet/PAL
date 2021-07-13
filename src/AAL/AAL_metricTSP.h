#pragma once

typedef struct metricTSP_instance {
  unsigned int numberOfVertices;
  void* metricSpace;
  float (*distance)(const unsigned int i, const unsigned int j, const void*);
} AAL_metricTSP_instance;

typedef struct metricTSP_result {
  unsigned int* permutation;
  unsigned int numberOfVertices;
  float objectiveValue;
} AAL_metricTSP_result;

#ifdef __cplusplus
extern "C" {
#endif

AAL_metricTSP_result AAL_metricTSP_nearest_addition(const AAL_metricTSP_instance instance);

#ifdef __cplusplus
}
#endif
