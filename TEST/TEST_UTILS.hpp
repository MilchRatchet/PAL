#pragma once
#include <string>

void print_lightgreen(const std::string word);
void print_lightred(const std::string word);
void print_yellow(const std::string word);
void print_check(const bool b, const std::string& str);

bool compareAryInt(const int* a, const unsigned int size_a, const int* b, const unsigned int size_b);
bool compareAryUInt(const unsigned int* a, const unsigned int size_a, const unsigned int* b, const unsigned int size_b);
