#include "setcover.h"

#include <vector>

setcoverResult setcover_greedy(setcoverInstance instance) {
  // int* set[instance.numberOfSubsets];
  unsigned int usedSets = 0;
  std::vector<int> remainingSets(instance.numberOfSubsets);
  for (unsigned int i = 0; i < instance.numberOfSubsets; ++i) {
  }
}
