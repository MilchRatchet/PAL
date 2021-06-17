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
  float objectiveValue;
};

/*!
 * \brief setcover_greedy
 * \param instance.subsets setcover_greedy expects the subsets subsequent in one vector
 * \param instance.subsetSizes is used to seperate the subsets
 */
setcoverResult AAL_setcover_greedy(setcoverInstance &instance);
