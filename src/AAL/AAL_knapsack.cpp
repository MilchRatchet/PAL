#include "AAL_knapsack.h"

#include <algorithm>
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
  for (unsigned int i = 0; i < instance.numberOfItems; ++i) {
    const unsigned int subsetsSize = subsets.size();
    for (unsigned int j = 0; j < subsetsSize; ++j) {
      // if there is enough space left add the item
      if (subsets[j].size() + instance.itemSizes[i] <= instance.capacity) {
        Subset newSubset = subsets[j];
        newSubset.addItem(instance.itemSizes[i], instance.itemValues[i], i);
        subsets.push_back(newSubset);
      }
      else {
        break;
      }
    }
    std::sort(subsets.begin(), subsets.end(), [](Subset a, Subset b) { return a.size() < b.size(); });
    // remove all dominated items
    float max_value = -1.0f;
    for (unsigned int j = 0; j < subsets.size(); ++j) {
      if (subsets[j].value() <= max_value) {
        subsets.erase(subsets.begin() + j);
        --j;
      }
      else {
        max_value = subsets[j].value();
      }
    }
  }
  const Subset bestSubset    = subsets[subsets.size() - 1];
  unsigned int numberOfItems = bestSubset.numElements();
  unsigned int* items        = (unsigned int*) malloc(numberOfItems * sizeof(unsigned int));
  for (unsigned int i = 0; i < numberOfItems; ++i) {
    items[i] = bestSubset.element(i);
  }
  AAL_knapsackResult result{items, numberOfItems, bestSubset.value()};
  return result;
}
