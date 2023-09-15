#include "input_output_copy.h"

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
