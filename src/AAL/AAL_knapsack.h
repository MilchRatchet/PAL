#pragma once

typedef struct knapsackInstance {
  float* itemSizes;
  float* itemValues;
  unsigned int numberOfItems;
  float capacity;
} AAL_knapsackInstance;

typedef struct knapsackResult {
  unsigned int* items;
  unsigned int numberOfItems;
  float objectiveValue;
} AAL_knapsackResult;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief AAL_knapsack_exact solves the knapsackproblem
 * \details Since the knapsack problem is solved to optimality this is not a polytime algorithm
 * \param instance
 * \return
 */
AAL_knapsackResult AAL_knapsack_exact(AAL_knapsackInstance instance);

#ifdef __cplusplus
}
#endif
