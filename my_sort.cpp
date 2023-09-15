#include "my_sort.h"

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
