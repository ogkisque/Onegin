#include "my_sort.h"

void swap_lines (void* left, void* right, size_t size_line)
{
    assert (left);
    assert (right);

    char* one = (char*) left;
    char* two = (char*) right;
    char tmp = '\0';
    for (size_t i = 0; i < size_line; i++)
    {
        tmp = one[i];
        one[i] = two[i];
        two[i] = tmp;
    }
}

int compare_str (const void* left, const void* right)
{
    assert (left);
    assert (right);

    const char* str_left = *((const char* const *) left);
    const char* str_right = *((const char* const *) right);

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

size_t partit (void* lines, size_t num_lines, size_t size_line, int (*comparator) (const void* a, const void* b))
{
    assert (lines);

    size_t left = 0;
    size_t right = num_lines;
    size_t i = left;
    size_t j = right;

    void* mid = (char*) lines + size_line * ((left + right) / 2);
    while (i < j)
    {
        while ((comparator ((char*) lines + i * size_line, mid) < 0) && (i < right))
            i++;
        while ((comparator ((char*) lines + j * size_line, mid) > 0) && (j > left))
            j--;
        if (i <= j)
        {
            swap_lines ((char*) lines + i * size_line, (char*) lines + j * size_line, size_line);
            if (i < right)
                i++;
            if (j > left)
                j--;
        }
    }

    return j;
}

void my_q_sort (void* lines, size_t num_lines, size_t size_line, int (*comparator) (const void* a, const void* b))
{
    assert (lines);
    assert (comparator);

    if (num_lines > 0)
    {
        size_t mid = partit (lines, num_lines, size_line, comparator);
        if (mid > 0)
            my_q_sort (lines, mid + 1, size_line, comparator);
        if (num_lines > mid + 1)
            my_q_sort ((char*) lines + size_line * mid + size_line, num_lines - mid - 1, size_line, comparator);
    }
}
