#pragma once

typedef struct MaxSatInstance {
  unsigned int numberOfClauses;
  unsigned int* clausesSizes;
  float* weights;
  int* clauses;
} AAL_MaxSatInstance;

typedef struct MaxSatResult {
  float objectiveValue;
  unsigned int numberOfVariables;
  unsigned int* variables;
  bool* variableStates;
  int status;
} AAL_MaxSatResult;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief AAL_MaxSat_unbiased assigne all variables randomly to true or false
 * \param instance
 * \details clauses contains all the literals of the clauses in the order they appear in the clauses. Positiv integers
 * stand for positive literals, the negation of variable i is expressed by -i. So don't use 0 as variable index;
 * \return
 */
AAL_MaxSatResult AAL_MaxSat_unbiased(const AAL_MaxSatInstance instance);

#ifdef __cplusplus
}
#endif
