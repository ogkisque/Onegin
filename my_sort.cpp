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

size_t partit (void* lines, size_t left, size_t right, size_t size_line, int (*comparator) (const void* a, const void* b))
{
    assert (lines);
    assert (comparator);

    size_t mid = (left + --right) / 2;

    size_t i = left;
    size_t j = right;

    while (i < j)
    {
        int comp_i = comparator ((char*) lines + i * size_line, (char*) lines + mid * size_line);
        int comp_j = comparator ((char*) lines + j * size_line, (char*) lines + mid * size_line);

        if (comp_i >= 0 && comp_j <= 0)
        {
            if (comparator ((char*) lines + i * size_line, (char*) lines + j * size_line) == 0)
            {
                i++;
            }
            else
            {
                if (i == mid)
                    mid = j;
                else if (j == mid)
                    mid = i;
                swap_lines ((char*) lines + i * size_line, (char*) lines + j * size_line, size_line);
                i++;
            }
        }
        if (comp_i < 0)
            i++;
        if (comp_j > 0)
            j--;
    }

    return i;
}

void my_q_sort (void* lines, size_t left, size_t right, size_t size_line, int (*comparator) (const void* a, const void* b))
{
    assert (lines);
    assert (comparator);

    if (right - left <= 1) return;

    size_t mid = partit (lines, left, right, size_line, comparator);
    my_q_sort (lines, left, mid, size_line, comparator);
    my_q_sort (lines, mid + 1, right, size_line, comparator);
}
