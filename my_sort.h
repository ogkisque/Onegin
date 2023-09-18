#ifndef MY_SORT_HEADER
#define MY_SORT_HEADER

#include <assert.h>
#include <ctype.h>
#include <stdio.h>

void swap_lines (void* left, void* right, size_t size_line);
int compare_str (const void* left, const void* right);
size_t partit (void* lines, size_t num_lines, size_t size_line, int (*comparator) (const void* a, const void* b));
void my_q_sort (void* lines, size_t num_lines, size_t size_line, int (*comparator) (const void* a, const void* b));

#endif //MY_SORT_HEADER
