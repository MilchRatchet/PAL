#include "AAL_knapsack.h"

#include <algorithm>
#include <tuple>
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

AAL_knapsackResult AAL_knapsack_exact(AAL_knapsackInstance instance) {
  Subset emptyset = Subset();
  std::vector<Subset> subsets{emptyset};
  std::vector<std::tuple<unsigned int, float>> indexes = {std::tuple<unsigned int, float>(0, 0.0f)};
  for (unsigned int i = 0; i < instance.numberOfItems; ++i) {
    const unsigned int indexesSize = indexes.size();
    for (unsigned int j = 0; j < indexesSize; ++j) {
      // if there is enough space left add the item
      if (subsets[std::get<0>(indexes[j])].size() + instance.itemSizes[i] <= instance.capacity) {
        Subset newSubset = subsets[std::get<0>(indexes[j])];
        newSubset.addItem(instance.itemSizes[i], instance.itemValues[i], i);
        subsets.push_back(newSubset);
        indexes.push_back(
          std::tuple<unsigned int, float>(subsets.size() - 1, std::get<1>(indexes[j]) + instance.itemSizes[i]));
      }
      else {
        break;
      }
    }
    std::sort(
      indexes.begin(), indexes.end(),
      [](const std::tuple<unsigned int, float> a, const std::tuple<unsigned int, float> b) {
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
