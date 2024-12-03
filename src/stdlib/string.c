#include "string.h"

void *memmove(void *dest, const void *src, size_t n)
{
    if (!src || !dest)
        return NULL;

    char *dest_char = dest;
    const char *src_char = src;

    if (dest == src)
        return dest;

    if (src_char > dest_char)
        for (size_t i = 0; i < n; ++i)
            *(dest_char + i) = *(src_char + i);
    else
        for (ssize_t i = n - 1; i >= 0; --i)
            *(dest_char + i) = *(src_char + i);

    return dest;
}

void itoa(int n, char *res)
{
    if (n == 0)
    {
        res[0] = '0';
        res[1] = 0;
        return;
    }
    if (n < 0)
    {
        n = -n;
        res[0] = '-';
        res++;
    }

    int digits = 0;

    int tmp = n;
    while (tmp)
    {
        digits++;
        tmp /= 10;
    }

    res[digits] = 0;

    while (digits)
    {
        int last = n % 10;
        res[digits - 1] = '0' + last;
        digits--;
        n /= 10;
    }
}

int atoi(char *str)
{
    int sign = 1 - 2 * (*str == '-');
    int res = 0;
    if (sign < 0)
        str++;
    while (*str && *str >= '0' && *str < '9')
    {
        res *= 10;
        res += *str - '0';
        str++;
    }

    return res * sign;
}

int strcmp(char *a, char *b)
{
    while (*a && *b && *a == *b)
    {
        a++;
        b++;
    }

    if (!*a && !*b)
    {
        return 0;
    }

    if (!*a)
    {
        return -1;
    }

    if (!*b)
    {
        return 1;
    }

    return *a - *b;
}

int strlen(char *s)
{
    int res = 0;
    while (s[res])
    {
        res++;
    }
    return res;
}
