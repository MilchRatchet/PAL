#include "TEST_knapsack.h"

#include <cmath>
#include <cstdlib>
#include <set>
#include <string>

#include "AAL_knapsack.h"
#include "TEST_UTILS.hpp"

void TEST_KNAPSACK(std::set<std::string> testset) {
  const unsigned int numberOfItems = 8;
  float* itemSizes                 = (float*) malloc(numberOfItems * sizeof(float));
  float* itemValues                = (float*) malloc(numberOfItems * sizeof(float));

  itemSizes[0] = 2.4f;
  itemSizes[1] = 0.6f;
  itemSizes[2] = 9.2f;
  itemSizes[3] = 5.2f;
  itemSizes[4] = 1.4f;
  itemSizes[5] = 5.9f;
  itemSizes[6] = 3.6f;
  itemSizes[7] = 0.0f;

  itemValues[0] = 1.7f;
  itemValues[1] = 0.4f;
  itemValues[2] = 2.2f;
  itemValues[3] = 4.4f;
  itemValues[4] = 0.9f;
  itemValues[5] = 6.0f;
  itemValues[6] = 2.1f;
  itemValues[7] = 5.4f;

  const float capacity = 8.8f;

  AAL_knapsackInstance instance{itemSizes, itemValues, numberOfItems, capacity};

  unsigned int* subset = (unsigned int*) malloc(3 * sizeof(unsigned int));
  subset[0]            = 0;
  subset[1]            = 5;
  subset[2]            = 7;

  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("KSE") != 0) {
    AAL_knapsackResult result = AAL_knapsack_exact(instance);

    print_check(
      std::abs(result.objectiveValue - 13.1f) < 0.00001f
        && compareAryUInt(result.items, result.numberOfItems, subset, 3),
      "AAL_KNAPSACK_EXACT");

    free(result.items);
  }
  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("KSF") != 0) {
    const float eps           = 0.1;
    AAL_knapsackResult result = AAL_knapsack_fptas(instance, eps);

    print_check(
      result.objectiveValue >= 13.1f * (1 - eps) - 0.00001f && result.objectiveValue <= 13.1f + 0.00001f
        && compareAryUInt(result.items, result.numberOfItems, subset, 3),
      "AAL_KNAPSACK_FPTAS");
    free(result.items);
  }
  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("KSM") != 0) {
    unsigned int* subset2 = (unsigned int*) malloc(5 * sizeof(unsigned int));
    subset2[0]            = 7;
    subset2[1]            = 0;
    subset2[2]            = 1;
    subset2[3]            = 4;
    subset2[4]            = 3;

    AAL_knapsackResult result = AAL_knapsack_min(instance);

    print_check(
      std::abs(result.objectiveValue - 9.6f) < 0.00001f
        && compareAryUInt(result.items, result.numberOfItems, subset2, 5),
      "AAL_MINIMUM_KNAPSACK");
    free(subset2);
    free(result.items);
  }

  free(instance.itemSizes);
  free(instance.itemValues);
  free(subset);
}
