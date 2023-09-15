#ifndef INPUT_OUTPUT_COPY_HEADER
#define INPUT_OUTPUT_COPY_HEADER

#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

enum Errors
{
    CORRECT          = -1,
    SIZE_FILE_ERR    =  1,
    OPEN_FILE_ERR    =  2,
    MEMORY_ALLOC_ERR =  3,
    COPY_FILE_ERR    =  4
};

struct Text
{
    char* buffer;
    size_t length;
    char** lines;
    size_t num_lines;
};

size_t get_file_size (const char* file_name, Errors* error);
char* memory_alloc (size_t size_file, Errors* error);
int copy_data (const char* file_name, char* buffer, size_t size_file, Errors* error);
char** create_lines_pointers (Text* text, Errors* error);

#endif //INPUT_OUTPUT_COPY_HEADER
