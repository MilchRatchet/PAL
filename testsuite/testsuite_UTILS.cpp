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
  std::cout << " " << str <<"\n";
}
