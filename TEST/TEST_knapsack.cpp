#include "TEST_knapsack.h"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

#include "AAL_knapsack.h"
#include "TEST_UTILS.hpp"

void TEST_KNAPSACK_EXACT() {
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
  AAL_knapsackResult result = AAL_knapsack_exact(instance);

  unsigned int* subset = (unsigned int*) malloc(3 * sizeof(unsigned int));
  subset[0]            = 0;
  subset[1]            = 5;
  subset[2]            = 7;

  print_check(
    std::abs(result.objectiveValue - 13.1f) < 0.00001f && compareAryUInt(result.items, result.numberOfItems, subset, 3),
    "AAL_KNAPSACK_EXACT");

  free(instance.itemSizes);
  free(instance.itemValues);
  free(result.items);
  free(subset);
}

void TEST_KNAPSACK_PERFORMANCE() {
  const unsigned int numberOfItems = 200;
  float* itemSizes                 = (float*) malloc(numberOfItems * sizeof(float));
  float* itemValues                = (float*) malloc(numberOfItems * sizeof(float));

  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(0.0f, 10.0f);

  for (unsigned int i = 0; i < numberOfItems; ++i) {
    itemSizes[i] = distribution(generator);
  }
  for (unsigned int i = 0; i < numberOfItems; ++i) {
    itemValues[i] = distribution(generator);
  }

  const float capacity = 5 * numberOfItems;

  AAL_knapsackInstance instance{itemSizes, itemValues, numberOfItems, capacity};
  auto start                = std::chrono::high_resolution_clock::now();
  AAL_knapsackResult result = AAL_knapsack_exact(instance);
  auto end                  = std::chrono::high_resolution_clock::now();
  auto duration             = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "timeconsumption: " << duration.count() << "\n";
  std::cout << "result: " << result.objectiveValue << "\n";
}
