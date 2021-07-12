#include "AAL_metricTSP.h"

#include <limits>
#include <numeric>
#include <stdexcept>
#include <vector>

metricTSP_result AAL_metricTSP_nearest_addition(const metricTSP_instance instance) {
  if (instance.numberOfVertices < 2) {
    throw std::runtime_error("Hamiltonian path on a graph with less than 2 nodes makes no sense.\n");
  }
  // find the 2 vertices with minimal distance
  float minimumDistance = std::numeric_limits<float>::max();
  unsigned int min_i, min_j;
  for (unsigned int i = 0; i < instance.numberOfVertices; ++i) {
    for (unsigned int j = 0; j < i; ++j) {
      if (instance.distance(i, j, instance.metricSpace) < minimumDistance) {
        minimumDistance = instance.distance(i, j, instance.metricSpace);
        min_i           = i;
        min_j           = j;
      }
    }
  }

  // initialize vector S of vertices in the hamiltonian path an T with the other vertices
  std::vector<unsigned int> S(instance.numberOfVertices);
  std::vector<unsigned int> T(instance.numberOfVertices);
  std::iota(T.begin(), T.end(), 0);
  S[0] = min_i;
  S[1] = min_j;
  std::swap(T[min_i], T[T.size() - 1]);
  T.pop_back();
  std::swap(T[min_j], T[T.size() - 1]);
  T.pop_back();

  // add the vertices to path
  while (T.size() > 0) {
    minimumDistance = std::numeric_limits<float>::max();
    for (unsigned int i = 0; i < S.size(); ++i) {
      for (unsigned int j = 0; j < T.size(); ++j) {
        if (instance.distance(S[i], T[j], instance.metricSpace) < minimumDistance) {
          minimumDistance = instance.distance(S[i], T[j], instance.metricSpace);
          min_i           = i;
          min_j           = j;
        }
      }
    }
    S.insert(S.begin() + min_i, T[min_j]);
    std::swap(T[min_j], T[T.size() - 1]);
    T.pop_back();
  }

  // compute the final objective value
  float objectiveValue = instance.distance(S[instance.numberOfVertices - 1], S[0], instance.metricSpace);
  for (unsigned int i = 1; i < instance.numberOfVertices; ++i) {
    objectiveValue += instance.distance(S[i - 1], S[i], instance.metricSpace);
  }

  // translate to output format
  unsigned int* permutation = (unsigned int*) malloc(instance.numberOfVertices * sizeof(unsigned int));
  for (unsigned int i = 0; i < instance.numberOfVertices; ++i) {
    permutation[i] = S[i];
  }

  metricTSP_result result{permutation, instance.numberOfVertices, objectiveValue};
  return result;
}
