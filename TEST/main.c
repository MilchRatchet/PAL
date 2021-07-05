#include "TEST_UTILS.h"
#include "TEST_CONVEXHULL.h"
#include "TEST_setcover.h"
#include "TEST_knapsack.h"

/*
 * This is supposed to test the libraries
 */
int main() {
  TEST_PRINT_START();
  TEST_CONVEXHULL_JARVIS();
  TEST_CONVEXHULL_CHAN();
  TEST_setcover();
  TEST_knapsack();
  return 0;
}
