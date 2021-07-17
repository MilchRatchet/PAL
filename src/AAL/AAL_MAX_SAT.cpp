#include "AAL_MAX_SAT.h"

#include <cmath>
#include <random>
#include <utility>
#include <vector>

enum Literal { _true, _false, _not_found };

Literal findVariable(const std::vector<std::pair<unsigned int, bool>> literals, const int var) {
  for (unsigned int k = 0; k < literals.size(); ++k) {
    if (std::get<0>(literals[k]) == (unsigned int) std::abs(var)) {
      if ((var > 0 && std::get<1>(literals[k]) == true) || (var < 0 && std::get<1>(literals[k]) == false)) {
        return _true;
      }
      else {
        return _false;
      }
    }
  }
  return _not_found;
}

MaxSatResult AAL_MaxSat_unbiased(const MaxSatInstance instance) {
  // set up a random generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> rand(0, 1);

  float objectiveValue = 0.0f;
  std::vector<std::pair<unsigned int, bool>> literals;
  unsigned int iterator = 0;
  for (unsigned int i = 0; i < instance.numberOfClauses; ++i) {
    for (unsigned int j = 0; j < instance.clausesSizes[i]; ++j) {
      int var     = instance.clauses[iterator];
      Literal lit = findVariable(literals, var);
      if (lit == _not_found) {
        bool state = (rand(gen) == 1);
        literals.push_back(std::pair<unsigned int, bool>{std::abs(var), state});
        if ((state == true && var > 0) || (state == false && var < 0)) {
          lit = _true;
        }
        else {
          lit = _false;
        }
      }
      if (lit == _true) {
        // the clause is satisfied and no other literals of the clause have to be considered
        objectiveValue += instance.weights[i];
        iterator += instance.clausesSizes[i] - j;
        break;
      }
      ++iterator;
    }
  }

  const unsigned int numberOfVariables = literals.size();
  unsigned int* variables              = (unsigned int*) malloc(sizeof(unsigned int) * numberOfVariables);
  bool* variableStates                 = (bool*) malloc(sizeof(bool) * numberOfVariables);
  for (unsigned int i = 0; i < literals.size(); ++i) {
    variables[i]      = std::get<0>(literals[i]);
    variableStates[i] = std::get<1>(literals[i]);
  }

  AAL_MaxSatResult result{objectiveValue, numberOfVariables, variables, variableStates, 0};
  return result;
}
