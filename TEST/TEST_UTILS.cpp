#include <iostream>
#include <string>

void print_lightgreen(const std::string word) {
  std::cout << "\033[1;32m";
  std::cout << word;
  std::cout << "\033[0m";
}

void print_lightred(const std::string word) {
  std::cout << "\033[1;31m";
  std::cout << word;
  std::cout << "\033[0m";
}

void print_yellow(const std::string word) {
  std::cout << "\033[1;33m";
  std::cout << word;
  std::cout << "\033[0m";
}

void print_check(const bool b, const std::string& str) {
  if (b) {
    print_lightgreen("[PASSED]");
  }
  else {
    print_lightred("[FAILED]");
  }
  std::cout << " " << str << "\n";
}

bool compareAryInt(const int* a, const unsigned int size_a, const int* b, const unsigned int size_b) {
  if (size_a != size_b) {
    return false;
  }
  for (unsigned int i = 0; i < size_a; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

bool compareAryUInt(
  const unsigned int* a, const unsigned int size_a, const unsigned int* b, const unsigned int size_b) {
  if (size_a != size_b) {
    return false;
  }
  for (unsigned int i = 0; i < size_a; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}
