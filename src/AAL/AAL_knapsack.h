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
 * \brief AAL_knapsack_exact solves the knapsack problem
 * \details Since the knapsack problem is solved to optimality this is not a polytime algorithm
 * \param instance item sizes, item values, number of items and capacity which specify the problem
 * \return objective value and a list of the item contained in the optimal solution
 */
AAL_knapsackResult AAL_knapsack_exact(const AAL_knapsackInstance instance);

/*!
 * \brief AAL_knapsack_fptas approximates the knapsack problem
 * \param instance item sizes, item values, number of items and capacity which specify the problem
 * \param eps factor for the approximation guarantee, objective value will be at least (1 - eps) OPT
 * \return objective value (based on original itemvalues) and item list of the rounded instance
 */
AAL_knapsackResult AAL_knapsack_fptas(const AAL_knapsackInstance instance, const float eps);

/*!
 * \brief AAL_knapsack_min
 * \param instance item sizes, item values, number of items and capacity which specify the problem
 * \details 2 approximation algorithm using the primal-dual method, for n items runtime is O(n)
 * \return objective value and a list of the items conatined in the approximated solution
 */
AAL_knapsackResult AAL_knapsack_min(const AAL_knapsackInstance instance);

#ifdef __cplusplus
}
#endif
