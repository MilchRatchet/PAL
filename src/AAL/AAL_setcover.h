#pragma once

typedef struct setcoverInstance {
  int* totalSet;
  unsigned int totalSetSize;
  int* subsets;
  unsigned int* subsetSizes;
  unsigned int numberOfSubsets;
  float* weights;
} AAL_setcoverInstance;

typedef struct setcoverResult {
  int* subsets;
  unsigned int numberOfSubsets;
  float objectiveValue;
} AAL_setcoverResult;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief setcover_greedy
 * \param instance.subsets setcover_greedy expects the subsets subsequent in one vector
 * \param instance.subsetSizes is used to seperate the subsets
 * \details weights have to be stricly positive
 */
AAL_setcoverResult AAL_setcover_greedy(AAL_setcoverInstance instance);

#ifdef __cplusplus
}
#endif
