#include <stdio.h>
#include <string.h>

#include "input_output_copy.h"
#include "my_sort.h"

#define CHECK_ERROR(error)          \
        if (error >= 0)             \
        {                           \
            errors_handler (error); \
            return 1;               \
        }

const size_t MAX_SIZE_FILE_NAME = 50;
const char* DEFAULT_FILE_NAME = "onegin.txt";

void errors_handler (Errors error);

int main (int args, char* argv[])
{
    char file_name[MAX_SIZE_FILE_NAME] = "";
    if (args == 2)
        strncpy (file_name, argv[1], MAX_SIZE_FILE_NAME);
    else
        strncpy (file_name, DEFAULT_FILE_NAME, MAX_SIZE_FILE_NAME);

    Errors error = CORRECT;
    Text text = {.buffer = NULL, .length = 0, .lines = NULL, .num_lines = 0};

    text_ctor (&text, file_name, &error);
    CHECK_ERROR(error);

    my_q_sort (text.lines, 0, text.num_lines, sizeof (char*), compare_str);

    print_text (&text);

    free (text.buffer);
    free (text.lines);

    return 0;
}

void errors_handler (Errors error)
{
    switch (error)
    {
        case SIZE_FILE_ERR:
            printf ("Error is in getting size of file\n");
            break;
        case OPEN_FILE_ERR:
            printf ("Error is in opening of file\n");
            break;
        case MEMORY_ALLOC_ERR:
            printf ("Error is in allocation memory\n");
            break;
        case COPY_FILE_ERR:
            printf ("Error is in copying of file\n");
            break;
        case CORRECT:
            break;
        default:
            break;
    }
}


