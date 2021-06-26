#include <stdio.h>

void TEST_PRINT_GREEN(char* str) {
  printf("\033[1;32m%s\033[0m", str);
}

void TEST_PRINT_RED(char* str) {
  printf("\033[1;31m%s\033[0m", str);
}
