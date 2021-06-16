#pragma once

struct setcoverInstance {
  int* totalSet;
  unsigned int totalSetSize;
  int* subsets;
  int* subsetSizes;
  unsigned int numberOfSubsets;
  int* weights;
};

struct setcoverResult {};
