#pragma once

struct setcoverInstance {
  int* totalSet;
  unsigned int totalSetSize;
  int* subsets;
  unsigned int* subsetSizes;
  unsigned int numberOfSubsets;
  float* weights;
};

struct setcoverResult {
  int* subsets;
  unsigned int numberOfSubsets;
  float objectiveValue;
};

#ifdef __cplusplus
  extern "C" {
#endif

/*!
 * \brief setcover_greedy
 * \param instance.subsets setcover_greedy expects the subsets subsequent in one vector
 * \param instance.subsetSizes is used to seperate the subsets
 * \details weights have to be stricly positive
 */
setcoverResult AAL_setcover_greedy(setcoverInstance &instance);

#ifdef __cplusplus
  }
#endif
