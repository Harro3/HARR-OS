#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "stdlib/def.h"

struct blk_meta
{
    struct blk_meta *next;
    struct blk_meta *prev;
    char is_free;
    size_t size;
    char *data[];
};

struct blk_allocator
{
    struct blk_meta *head;
    char *end;
};

void *blk_alloc(size_t size);
void blk_free(void *ptr);

#endif
