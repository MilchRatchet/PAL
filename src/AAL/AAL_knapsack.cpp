#include "AAL_knapsack.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

class Subset {
private:
  float p_size;
  float p_value;
  std::vector<unsigned int> p_set;

public:
  Subset() {
    p_size  = 0.0f;
    p_value = 0.0f;
    p_set.resize(0);
  }
  void addItem(const float size, const float value, const unsigned int item) {
    p_size += size;
    p_value += value;
    p_set.push_back(item);
  }

  float size() const {
    return this->p_size;
  }

  float value() const {
    return this->p_value;
  }

  unsigned int numElements() const {
    return p_set.size();
  }

  unsigned int element(const unsigned int i) const {
    return p_set[i];
  }
};

AAL_knapsackResult AAL_knapsack_exact(const AAL_knapsackInstance instance) {
  const Subset emptyset = Subset();
  std::vector<Subset> subsets{emptyset};
  std::vector<std::pair<unsigned int, float>> indexes = {std::pair<unsigned int, float>(0, 0.0f)};
  for (unsigned int i = 0; i < instance.numberOfItems; ++i) {
    const unsigned int indexesSize = indexes.size();
    for (unsigned int j = 0; j < indexesSize; ++j) {
      // if there is enough space left add the item
      if (subsets[std::get<0>(indexes[j])].size() + instance.itemSizes[i] <= instance.capacity) {
        Subset newSubset = subsets[std::get<0>(indexes[j])];
        newSubset.addItem(instance.itemSizes[i], instance.itemValues[i], i);
        subsets.push_back(newSubset);
        indexes.push_back(
          std::pair<unsigned int, float>(subsets.size() - 1, std::get<1>(indexes[j]) + instance.itemSizes[i]));
      }
      else {
        break;
      }
    }
    std::sort(
      indexes.begin(), indexes.end(),
      [](const std::pair<unsigned int, float> a, const std::pair<unsigned int, float> b) {
        return std::get<1>(a) < std::get<1>(b);
      });
    // remove all dominated items
    float max_value = -1.0f;
    for (unsigned int j = 0; j < indexes.size(); ++j) {
      if (subsets[std::get<0>(indexes[j])].value() <= max_value) {
        indexes.erase(indexes.begin() + j);
        --j;
      }
      else {
        max_value = subsets[std::get<0>(indexes[j])].value();
      }
    }
  }
  const Subset bestSubset    = subsets[std::get<0>(indexes[indexes.size() - 1])];
  unsigned int numberOfItems = bestSubset.numElements();
  unsigned int* items        = (unsigned int*) malloc(numberOfItems * sizeof(unsigned int));
  for (unsigned int i = 0; i < numberOfItems; ++i) {
    items[i] = bestSubset.element(i);
  }
  AAL_knapsackResult result{items, numberOfItems, bestSubset.value()};
  return result;
}

AAL_knapsackResult AAL_knapsack_fptas(const AAL_knapsackInstance instance, const float eps) {
  // check there is no access to non existing data
  if (instance.numberOfItems == 0) {
    throw std::runtime_error("AAL_knapsack_fptas can't handle empty instances.\n");
  }
  // compute \mu
  float mu = instance.itemValues[0];
  for (unsigned int i = 1; i < instance.numberOfItems; ++i) {
    if (instance.itemValues[i] > mu && instance.itemValues[i] <= instance.capacity) {
      mu = instance.itemValues[i];
    }
  }
  mu *= eps / instance.numberOfItems;
  // round the values
  float* roundedItemValues = (float*) malloc(instance.numberOfItems * sizeof(float));
  for (unsigned int i = 0; i < instance.numberOfItems; ++i) {
    roundedItemValues[i] = std::floor(instance.itemValues[i] / mu) * mu;
  }
  AAL_knapsackInstance roundedInstance{
    instance.itemSizes, roundedItemValues, instance.numberOfItems, instance.capacity};
  // invoke the exact knapsack on the rounded data
  AAL_knapsackResult result = AAL_knapsack_exact(roundedInstance);
  free(roundedItemValues);
  // retranslate the solution on the rounded data to the original data
  float objectiveValue = 0.0f;
  for (unsigned int i = 0; i < result.numberOfItems; ++i) {
    objectiveValue += instance.itemValues[result.items[i]];
  }
  result.objectiveValue = objectiveValue;
  return result;
}

AAL_knapsackResult AAL_knapsack_min(const AAL_knapsackInstance instance) {
  // copy sizes and values into vectors
  std::vector<unsigned int> zeros;
  std::vector<float> sizes(instance.numberOfItems), values(instance.numberOfItems);
  for (unsigned int i = 0; i < instance.numberOfItems; ++i) {
    sizes[i]  = instance.itemSizes[i];
    values[i] = instance.itemValues[i];
    if (values[i] == 0) {
      zeros.push_back(i);  // keep track of zeros, because later will be divided by values
    }
  }

  std::vector<unsigned int> A, A_complement(instance.numberOfItems);
  std::iota(A_complement.begin(), A_complement.end(), 0);
  // items of value 0 will be no longer considered
  for (int i = zeros.size() - 1; i >= 0; ++i) {
    std::swap(A_complement[A_complement.size() - 1], A_complement[zeros[i]]);
    A_complement.pop_back();
  }

  float value = 0;
  while (value < instance.capacity) {
    if (A_complement.size() == 0) {
      throw std::logic_error("Minimum knapsack is infeasible on that instance!");
    }
    // cap the item values to the value gap left and
    // find the constraint the becomes tight first
    float min              = std::numeric_limits<float>::max();
    unsigned int min_index = 0;
    for (unsigned int i = 0; i < A_complement.size(); ++i) {
      values[A_complement[i]] = std::min(values[A_complement[i]], instance.capacity - value);
      if (sizes[A_complement[i]] / values[A_complement[i]] < min) {
        min       = sizes[A_complement[i]] / values[A_complement[i]];
        min_index = i;
      }
    }

    value += instance.itemValues[A_complement[min_index]];
    A.push_back(A_complement[min_index]);
    // remove the element from the remaining elements A_complement
    std::swap(A_complement[min_index], A_complement[A_complement.size() - 1]);
    A_complement.pop_back();

    // reduce the sizes by the value times the dual variable
    for (unsigned int i = 0; i < A_complement.size(); ++i) {
      sizes[A_complement[i]] -= min * values[A_complement[i]];
    }
  }

  // construct the solution
  unsigned int* items  = (unsigned int*) malloc(A.size() * sizeof(unsigned int));
  float objectiveValue = 0;
  for (unsigned int i = 0; i < A.size(); ++i) {
    objectiveValue += instance.itemSizes[A[i]];
    items[i] = A[i];
  }

  knapsackResult result{items, (unsigned int) A.size(), objectiveValue};
  return result;
}
