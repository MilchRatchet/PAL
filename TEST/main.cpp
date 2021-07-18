#include <iostream>
#include <set>
#include <string>

#include "TEST_CONVEXHULL.h"
#include "TEST_knapsack.h"
#include "TEST_MAX_SAT.h"
#include "TEST_metricTSP.h"
#include "TEST_setcover.h"
#include "TEST_UTILS.h"

/*
 * select tests
 */

void select_tests(int argc, char** argv) {
  std::set<std::string> testset;
  for (int i = 1; i < argc; ++i) {
    testset.insert({std::string(argv[i])});
  }
  if (testset.count("HELP") != 0 || argc == 1) {
    std::cout << "Helppage\n========\n";
    std::cout << "Pass argument <FULL> to test all algorithms.\n";
    std::cout << "Pass argument <AAL> to test all algorithms from the approximation algorithm library.\n";
    std::cout << "Pass argument <CGL> to test all algorithms from the computational geometry library.\n";
    std::cout << "Pass any abbreviation to select specific algorithms to test.\n";
    std::cout << "You can combine several of these in any order to test several algorithms.\n";
    std::cout << "Below you can find a list of available abbreviations:\n";
    std::cout << "Abbreviation | Library | Algorithm\n";
    std::cout << "-------------|---------|-------------------\n";
    std::cout << "     KSE     |   AAL   | knapsack exact\n";
    std::cout << "     KSF     |   AAL   | knapsack FPTAS\n";
    std::cout << "     KSM     |   AAL   | minimum knapsack\n";
    std::cout << "     MSU     |   AAL   | MAX SAT unbiased\n";
    std::cout << "     SCG     |   AAL   | setcover greedy\n";
    std::cout << "     TSN     |   AAL   | metric TSP nearest addition\n";
    std::cout << "     CHC     |   CGL   | convex hull chan\n";
    std::cout << "     CHJ     |   CGL   | convex hull jarvis\n";
  }

  if (
    testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("KSE") != 0 || testset.count("KSF") != 0
    || testset.count("KSM") != 0) {
    TEST_KNAPSACK(testset);
  }
  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("MSU") != 0) {
    TEST_MAX_SAT_unbiased();
  }
  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("SCG") != 0) {
    TEST_SETCOVER_GREEDY();
  }
  if (testset.count("FULL") != 0 || testset.count("AAL") != 0 || testset.count("TSN") != 0) {
    TEST_METRIC_TSP_NEAREST_ADDITION();
  }
  if (testset.count("FULL") != 0 || testset.count("CGL") != 0 || testset.count("CHC") != 0) {
    TEST_CONVEXHULL_CHAN();
  }
  if (testset.count("FULL") != 0 || testset.count("CGL") != 0 || testset.count("CHJ") != 0) {
    TEST_CONVEXHULL_JARVIS();
  }
}

/*
 * This is supposed to test the libraries
 */
int main(int argc, char** argv) {
  TEST_PRINT_START();
  select_tests(argc, argv);
  return 0;
}
