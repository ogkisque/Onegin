#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

enum Errors
{
    CORRECT          = -1,
    SIZE_FILE_ERR    =  1,
    OPEN_FILE_ERR    =  2,
    MEMORY_ALLOC_ERR =  3,
    COPY_FILE_ERR    =  4
};

const char* FILE_NAME = "onegin.txt";

size_t get_file_size (Errors* error);
void errors_handler (Errors error);
char* memory_alloc (Errors* error, size_t size_file);
int copy_data (char* buffer, Errors* error, size_t size_file);
char** create_lines_pointers (size_t* num_lines, char* buffer, size_t length, Errors* error);

int main ()
{
    Errors error = CORRECT;

    size_t size_file = get_file_size (&error);
    if (error >= 0)
    {
        errors_handler (error);
        return 1;
    }
    size_t length = size_file / sizeof (char);

    char* buffer = memory_alloc (&error, size_file);
    if (error >= 0)
    {
        errors_handler (error);
        return 1;
    }

    copy_data (buffer, &error, size_file);
    if (error >= 0)
    {
        errors_handler (error);
        return 1;
    }

    buffer[length + 1] = '\n';
    size_t num_lines = 0;
    char** lines = create_lines_pointers (&num_lines, buffer, length, &error);

    if (error >= 0)
    {
        errors_handler (error);
        return 1;
    }

    for (size_t i = 0; i < num_lines; i++)
        puts (lines[i]);

    return 0;
}

size_t get_file_size (Errors* error)
{
    assert (error);

    struct stat st;

    if (stat (FILE_NAME, &st) == -1)
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

char* memory_alloc (Errors* error, size_t size_file)
{
    assert (error);

    char* buffer = (char*) calloc (size_file / sizeof (char) + 1, sizeof (char));

    if (buffer)
        return buffer;

    *error = MEMORY_ALLOC_ERR;
    return NULL;
}

int copy_data (char* buffer, Errors* error, size_t size_file)
{
    assert (buffer);
    assert (error);

    FILE* file = fopen (FILE_NAME, "r");

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

char** create_lines_pointers (size_t* num_lines, char* buffer, size_t length, Errors* error)
{
    char** lines = (char**) calloc (length, sizeof (char*));
    if (lines == NULL)
    {
        *error = MEMORY_ALLOC_ERR;
        return 0;
    }

    lines[0] = buffer;
    *num_lines = 1;
    for (size_t i = 0; i < length; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            lines[*num_lines] = &buffer[i+1];
            (*num_lines)++;
        }
    }

    lines = (char**) realloc (lines, *num_lines * sizeof (char*));
    return lines;
}



