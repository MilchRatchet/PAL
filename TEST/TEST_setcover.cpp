#include "TEST_setcover.h"

#include <fstream>

#include "AAL_setcover.h"
#include "TEST_UTILS.hpp"

extern "C" void TEST_SETCOVER_GREEDY() {
  int* totalSet                = (int*) malloc(sizeof(int) * 8);
  unsigned int totalSetSize    = 8;
  int* subsets                 = (int*) malloc(sizeof(int) * 16);
  unsigned int* subsetSizes    = (unsigned int*) malloc(sizeof(unsigned int) * 5);
  unsigned int numberOfSubsets = 5;
  float* weights               = (float*) malloc(sizeof(float) * 5);

  for (size_t i = 0; i < totalSetSize; ++i) {
    totalSet[i] = i;
  }

  for (size_t i = 0; i < numberOfSubsets; ++i) {
    subsetSizes[i] = 3;
    weights[i]     = i + 1.0f;
  }

  // the middle vertex has degree 4
  subsetSizes[4] = 4;

  // list the objects contained by the subsets
  subsets[0]  = 0;
  subsets[1]  = 4;
  subsets[2]  = 3;
  subsets[3]  = 0;
  subsets[4]  = 5;
  subsets[5]  = 1;
  subsets[6]  = 1;
  subsets[7]  = 6;
  subsets[8]  = 2;
  subsets[9]  = 2;
  subsets[10] = 7;
  subsets[11] = 3;
  subsets[12] = 4;
  subsets[13] = 5;
  subsets[14] = 6;
  subsets[15] = 7;

  // the indexes of the subsets the should be the result of the algorithm
  int* subsets_cmp = (int*) malloc(sizeof(int) * 4);
  for (unsigned int i = 0; i < 4; ++i) {
    subsets_cmp[i] = i;
  }

  // create an instance for the setcover problem
  setcoverInstance instance{totalSet, totalSetSize, subsets, subsetSizes, numberOfSubsets, weights};
  // run the greedy setcover algorithm
  setcoverResult result = AAL_setcover_greedy(instance);

  print_check(
    result.objectiveValue == 10.0f && compareAryInt(result.subsets, result.numberOfSubsets, subsets_cmp, 4),
    "AAL_SETCOVER_GREEDY");

  free(totalSet);
  free(instance.subsets);
  free(instance.subsetSizes);
  free(instance.weights);

  free(result.subsets);
  free(subsets_cmp);
}
