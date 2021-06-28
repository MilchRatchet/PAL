#include <stdio.h>
#include "TEST_UTILS.h"

void TEST_PRINT_RESULT(int success, char* str) {
  TEST_PRINT_CLEAR();

  if (success) {
    TEST_PRINT_GREEN("[PASSED]");
  }
  else {
    TEST_PRINT_RED("[FAILED]");
  }

  printf(" %s\n", str);
}

void TEST_PRINT_INPROGRESS(char* str) {
  TEST_PRINT_YELLOW("[VERIFY]");
  printf(" %s", str);
  fflush(stdout);
}

void TEST_PRINT_GREEN(char* str) {
  printf("\033[1;32m%s\033[0m", str);
}

void TEST_PRINT_RED(char* str) {
  printf("\033[1;31m%s\033[0m", str);
}

void TEST_PRINT_YELLOW(char* str) {
  printf("\033[1;33m%s\033[0m", str);
}

void TEST_PRINT_CLEAR() {
  printf(
    "\r                                                                                                        \r");
}
