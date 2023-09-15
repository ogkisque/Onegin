#ifndef MY_SORT_HEADER
#define MY_SORT_HEADER

#include <assert.h>
#include <ctype.h>
#include <stdio.h>

void swap_lines (char** lines, size_t left, size_t right);
int compare_str (const char* str_left, const char* str_right);
size_t partit (char** lines, size_t left, size_t right);
void my_q_sort (char** lines, size_t left, size_t right);

#endif //MY_SORT_HEADER
