#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void TEST_PRINT_START();
void TEST_PRINT_RESULT(int success, char* str);
void TEST_PRINT_INPROGRESS(char* str);
void TEST_PRINT_GREEN(char* str);
void TEST_PRINT_RED(char* str);
void TEST_PRINT_YELLOW(char* str);
void TEST_PRINT_CLEAR();

#ifdef __cplusplus
}
#endif

#endif /* TEST_UTILS_H */
