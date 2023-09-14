#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define CHECK_ERROR(error)\
        if (error >= 0)\
        {\
            errors_handler (error);\
            return 1;\
        }

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

const size_t MAX_SIZE_FILE_NAME = 50;

size_t get_file_size (const char* file_name, Errors* error);
void errors_handler (Errors error);
char* memory_alloc (size_t size_file, Errors* error);
int copy_data (const char* file_name, char* buffer, size_t size_file, Errors* error);
char** create_lines_pointers (Text* text, Errors* error);
void swap_lines (char** lines, size_t left, size_t right);
int compare_str (const char* str_left, const char* str_right);
size_t partit (char** lines, size_t left, size_t right);
void my_q_sort (char** lines, size_t left, size_t right);

int main (int args, char* argv[])
{
    char file_name[MAX_SIZE_FILE_NAME] = "";
    if (args == 2)
        strncpy (file_name, argv[1], MAX_SIZE_FILE_NAME);
    else
        strncpy (file_name, "onegin.txt", MAX_SIZE_FILE_NAME);

    Errors error = CORRECT;
    Text text = {.buffer = NULL, .length = 0, .lines = NULL, .num_lines = 0};

    size_t size_file = get_file_size (file_name, &error);
    CHECK_ERROR(error);

    text.length = size_file / sizeof (char);

    text.buffer = memory_alloc (size_file, &error);
    CHECK_ERROR(error);

    copy_data (file_name, text.buffer, size_file, &error);
    CHECK_ERROR(error);

    (text.buffer)[text.length + 1] = '\n';
    text.num_lines = 0;
    text.lines = create_lines_pointers (&text, &error);
    CHECK_ERROR(error);

    my_q_sort (text.lines, 0, text.num_lines - 1);

    for (size_t i = 0; i < text.num_lines; i++)
        puts ((text.lines)[i]);

    free (text.buffer);
    free (text.lines);

    return 0;
}

size_t get_file_size (const char* file_name, Errors* error)
{
    assert (error);

    struct stat st;

    if (stat (file_name, &st) == -1)
    {
        *error = SIZE_FILE_ERR;
        return 0;
    }

    size_t size_file = st.st_size;
    return size_file;
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

char* memory_alloc (size_t size_file, Errors* error)
{
    assert (error);

    char* buffer = (char*) calloc (size_file / sizeof (char) + 1, sizeof (char));

    if (buffer)
        return buffer;

    *error = MEMORY_ALLOC_ERR;
    return NULL;
}

int copy_data (const char* file_name, char* buffer, size_t size_file, Errors* error)
{
    assert (buffer);
    assert (error);

    FILE* file = fopen (file_name, "r");

    if (file == NULL)
    {
        *error = OPEN_FILE_ERR;
        return 0;
    }

    size_t num_read = fread (buffer, sizeof (char), size_file / sizeof (char), file);

    if (!num_read)
    {
        *error = COPY_FILE_ERR;
        return 0;
    }

    return 1;
}

char** create_lines_pointers (Text* text, Errors* error)
{
    assert (text);
    assert (error);

    char** lines = (char**) calloc (text->length, sizeof (char*));
    if (lines == NULL)
    {
        *error = MEMORY_ALLOC_ERR;
        return 0;
    }

    lines[0] = text->buffer;
    text->num_lines = 1;
    for (size_t i = 0; i < text->length; i++)
    {
        if ((text->buffer)[i] == '\n')
        {
            (text->buffer)[i] = '\0';
            lines[text->num_lines] = &((text->buffer)[i+1]);
            (text->num_lines)++;
        }
    }

    lines = (char**) realloc (lines, text->num_lines * sizeof (char*));
    return lines;
}

void swap_lines (char** lines, size_t left, size_t right)
{
    assert (lines);

    char* tmp = lines[left];
    lines[left] = lines[right];
    lines[right] = tmp;
}

int compare_str (const char* str_left, const char* str_right)
{
    assert (str_left);
    assert (str_right);

    int ans = 0;
    size_t i = 0;
    size_t j = 0;

    while (str_left[i] != '\0' && str_right[j] != '\0')
    {
        if (!isalpha (str_left[i]))
        {
            i++;
            continue;
        }
        if (!isalpha (str_right[j]))
        {
            j++;
            continue;
        }

        if (toupper (str_left[i]) > toupper (str_right[j]))
            ans = 1;
        if (toupper (str_left[i]) < toupper (str_right[j]))
            ans = -1;
        if (ans != 0)
            break;
        i++;
        j++;
    }
    return ans;
}

size_t partit (char** lines, size_t left, size_t right)
{
    assert (lines);

    char* mid = lines[(left + right) / 2];

    size_t i = left;
    size_t j = right;
    while (i < j)
    {
        while (compare_str (lines[i], mid) < 0)
            i++;
        while (compare_str (lines[j], mid) > 0)
            j--;
        if (i <= j)
        {
            swap_lines (lines, i, j);
            if (i < right)
                i++;
            if (j > left)
                j--;
        }
    }

    return j;
}

void my_q_sort (char** lines, size_t left, size_t right)
{
    assert (lines);

    if (left < right)
    {
        size_t mid = partit (lines, left, right);
        if (left < mid)
            my_q_sort (lines, left, mid);
        if (mid + 1 < right)
            my_q_sort (lines, mid + 1, right);
    }
}
