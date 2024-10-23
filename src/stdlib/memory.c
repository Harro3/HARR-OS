#include "stdlib/memory.h"

#include "allocator/allocator.h"

void *malloc(size_t size)
{
    return blk_alloc(size);
}

void *calloc(size_t nmemb, size_t size)
{
    char *ptr = malloc(nmemb * size);
    for (size_t i = 0; i < nmemb * size; i++)
    {
        ptr[i] = 0;
    }

    return ptr;
}

void free(void *ptr)
{
    blk_free(ptr);
}

void *realloc(void *ptr, size_t size)
{
    free(ptr);
    return malloc(size);
}
