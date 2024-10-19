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
