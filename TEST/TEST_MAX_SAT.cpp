#include "TEST_MAX_SAT.h"

#include <cstdlib>

#include "TEST_UTILS.hpp"

#include "AAL_MAX_SAT.h"

void TEST_MAX_SAT_unbiased() {
  unsigned int numberOfClauses = 5;
  unsigned int* clausesSizes   = (unsigned int*) malloc(sizeof(unsigned int) * numberOfClauses);
  float* weights               = (float*) malloc(sizeof(float) * numberOfClauses);
  int* clauses                 = (int*) malloc(sizeof(int) * 18);

  clausesSizes[0] = 3;
  clausesSizes[1] = 5;
  clausesSizes[2] = 4;
  clausesSizes[3] = 2;
  clausesSizes[4] = 4;

  weights[0] = 4.5f;
  weights[1] = 3.1f;
  weights[2] = 0.2f;
  weights[3] = 1.9f;
  weights[4] = 3.8f;

  clauses[0] = 1;
  clauses[1] = -3;
  clauses[2] = 4;

  clauses[3] = -4;
  clauses[4] = 5;
  clauses[5] = -1;
  clauses[6] = -2;
  clauses[7] = 3;

  clauses[8]  = 2;
  clauses[9]  = -3;
  clauses[10] = -1;
  clauses[11] = -6;

  clauses[12] = -5;
  clauses[13] = 2;

  clauses[14] = 3;
  clauses[15] = 6;
  clauses[16] = -2;
  clauses[17] = -4;

  AAL_MaxSatInstance instance{numberOfClauses, clausesSizes, weights, clauses};

  /*
   * ATTENTION: The test of this algorithm has a big draw back because of dealing with rondomness. The test is marked as
   * passed if the empiric median of 200 calls of the algorithm is at least half the optimal value, since the algorithm
   * guarantes to be a 0.5 approximation in expectation.
   * Never the less the tests lags because it is impossible to produce a solution that doesn't fullfill this bound, but
   * the bound would be tight only in the case of only unit clauses, which is also not a good test.
   * Just to mention: The expected value for the particular instance is 12 + 37/320.
   */
  float sumOV    = 0.0f;
  unsigned int n = 200;
  for (unsigned int i = 0; i < n; ++i) {
    AAL_MaxSatResult result = AAL_MaxSat_unbiased(instance);
    sumOV += result.objectiveValue;
    free(result.variables);
    free(result.variableStates);
  }
  print_check(sumOV / n >= 6.25, "AAL_MAX_SAT_UNBIASED");

  free(clausesSizes);
  free(weights);
  free(clauses);
}
