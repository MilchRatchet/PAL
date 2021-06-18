#include "AAL_setcover.h"

#include <algorithm>
#include <vector>

#include <iostream>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  const size_t size = vec.size();
  for (size_t i = 0; i < size; ++i)
    os << vec[i] << (i == size - 1 ? "" : " ");
  return os << std::endl;
}

template <typename T>
static size_t indexMax(const std::vector<T>& vec) {
  size_t index = 0;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec[i] > vec[index]) {
      index = i;
    }
  }
  return index;
}

template <typename T>
static void remove(std::vector<T>& vec1, const std::vector<T>& vec2) {
  if (vec1.size() > 0 && vec2.size() > 0) {
    std::sort(vec1.begin(), vec1.end());
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
      if (indexes[k] == vec1.size() - 1) {
        vec1.pop_back();
      }
      else {
        std::swap(vec1[indexes[k]], vec1[vec1.size() - 1]);
        vec1.pop_back();
      }
    }
  }
}

extern "C" setcoverResult AAL_setcover_greedy(setcoverInstance& instance) {
  // rewrite the data in a more comftable vector datastructure
  std::vector<std::vector<int>> remainingSets(instance.numberOfSubsets);
  std::vector<int> remainingObjects(instance.totalSetSize);
  size_t iterator = 0;
  for (unsigned int i = 0; i < instance.numberOfSubsets; ++i) {
    remainingSets[i].resize(instance.subsetSizes[i]);
    for (size_t j = 0; j < instance.subsetSizes[i]; ++j) {
      remainingSets[i][j] = instance.subsets[iterator];
      ++iterator;
    }
  }

  // initialize the remeining set
  for (size_t i = 0; i < instance.totalSetSize; ++i) {
    remainingObjects[i] = instance.totalSet[i];
  }

  // size_t remainingObjects = instance.totalSetSize;
  std::vector<float> sums(instance.numberOfSubsets);
  std::vector<float> ratio(instance.numberOfSubsets);

  // DEBUG
  unsigned int count = 0;

  // the main algorithm
  std::vector<int> choosenSets;
  while (remainingObjects.size() > 0 && count < instance.numberOfSubsets) {
    for (size_t i = 0; i < instance.numberOfSubsets; ++i) {
      ratio[i] = remainingSets[i].size() / instance.weights[i];
    }
    size_t index = indexMax(ratio);
    choosenSets.push_back(index);
    std::sort(remainingSets[index].begin(), remainingSets[index].end());
    for (size_t i = 0; i < instance.numberOfSubsets; ++i) {
      if (index != i) {
        remove(remainingSets[i], remainingSets[index]);
      }
    }
    // check there are still objects left
    remove(remainingObjects, remainingSets[index]);
    remainingSets[index].resize(0);  // make sure this set won't be considered a second time
    ++count;
  }

  // convert result to the output struct
  int* subsets         = (int*)malloc(sizeof (int)*choosenSets.size ());
  float objectiveValue = 0;
  setcoverResult result{subsets,objectiveValue};
  for (size_t i = 0; i < choosenSets.size(); ++i) {
    result.subsets[i] = choosenSets[i];
    result.objectiveValue += instance.weights[choosenSets[i]];
  }

  return result;
}
