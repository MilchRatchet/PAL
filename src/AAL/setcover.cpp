#include "setcover.h"

#include <algorithm>
#include <vector>

template <typename T>
size_t indexMax(const std::vector<T>& vec) {
  size_t index = 0;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] > vec[index]) {
      index = 0;
    }
  }
  return index;
}

template <typename T>
void remove(std::vector<T>& vec1, std::vector<T>& vec2, double& sum) {
  std::sort(vec1.begin(), vec1.end());
  std::sort(vec2.begin(), vec2.end());
  std::vector<size_t> indexes;
  size_t i = 0, j = 0;
  while (i < vec1.size() && j < vec2.size()) {
    if (vec1[i] < vec2[j]) {
      ++i;
    }
    else if (vec1[i] == vec2[j]) {
      indexes.push_back(i);
      ++i;
    }
    else {
      ++j;
    }
  }

  for (int k = indexes.size() - 1; k >= 0; --k) {
    sum -= vec1[indexes[k]];
    if (indexes[k] == vec1.size() - 1) {
      vec1.pop_back();
    }
    else {
      std::swap(vec1[indexes[k]], vec1[vec1.size() - 1]);
      vec1.pop_back();
    }
  }
}

setcoverResult setcover_greedy(setcoverInstance instance) {
  // rewrite the data in a more comftable vector datastructure
  std::vector<std::vector<int>> remainingSets(instance.numberOfSubsets);
  size_t iterator = 0;
  for (unsigned int i = 0; i < instance.numberOfSubsets; ++i) {
    remainingSets[i].resize(instance.subsetSizes[i]);
    for (size_t j = 0; j < instance.subsetSizes[i]; ++j) {
      remainingSets[i][j] = instance.totalSet[iterator];
      ++iterator;
    }
  }

  size_t remainingObjects = instance.totalSetSize;
  std::vector<double> sums(instance.numberOfSubsets);
  std::vector<double> ratio(instance.numberOfSubsets);

  // initialize the values for all given subsets
  for (size_t i = 0; instance.numberOfSubsets; ++i) {
    double sum = 0;
    for (size_t j = 0; j < instance.subsetSizes[i]; ++j) {
      sum += remainingSets[i][j];
    }
    sums[i] = sum;
  }

  // the main algorithm
  std::vector<int> choosenSets;
  while (remainingObjects > 0) {
    for (size_t i = 0; instance.numberOfSubsets; ++i) {
      ratio[i] = sums[i] / remainingSets[i].size();
    }
    size_t index = indexMax(ratio);
    choosenSets.push_back(index);
    for (size_t i = 0; i < instance.numberOfSubsets; ++i) {
      remove(remainingSets[i], remainingSets[index], sums[i]);
    }
  }

  // check there are still objects left
  remainingObjects = 0;
  for (size_t i = 0; i < instance.numberOfSubsets; ++i) {
    remainingObjects += remainingSets[i].size();
  }

  // convert result to the output struct

}
