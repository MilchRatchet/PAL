#include "TEST_knapsack.h"

#include <cmath>
#include <cstdlib>

#include "AAL_knapsack.h"
#include "TEST_UTILS.hpp"

void TEST_knapsack() {
  const unsigned int numberOfItems = 8;
  float* itemSizes                 = (float*) malloc(numberOfItems * sizeof(float));
  float* itemValues                = (float*) malloc(numberOfItems * sizeof(float));

  itemSizes[0] = 2.4;
  itemSizes[1] = 0.6;
  itemSizes[2] = 9.2;
  itemSizes[3] = 5.2;
  itemSizes[4] = 1.4;
  itemSizes[5] = 5.9;
  itemSizes[6] = 3.6;
  itemSizes[7] = 0.0;

  itemValues[0] = 1.7;
  itemValues[1] = 0.4;
  itemValues[2] = 2.2;
  itemValues[3] = 4.4;
  itemValues[4] = 0.9;
  itemValues[5] = 6.0;
  itemValues[6] = 2.1;
  itemValues[7] = 5.4;

  const float capacity = 8.8;

  AAL_knapsackInstance instance{itemSizes, itemValues, numberOfItems, capacity};
  AAL_knapsackResult result = AAL_knapsack_exact(instance);

  unsigned int* subset = (unsigned int*) malloc(3 * sizeof(unsigned int));
  subset[0]            = 0;
  subset[1]            = 5;
  subset[2]            = 7;

  print_check(
    std::abs(result.objectiveValue - 13.1) < 0.00001 && compareAryUInt(result.items, result.numberOfItems, subset, 3),
    "AAL_KNAPSACK_EXACT");

  free(instance.itemSizes);
  free(instance.itemValues);
  free(result.items);
  free(subset);
}
