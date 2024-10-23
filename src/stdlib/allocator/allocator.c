#include "allocator.h"

#define PAGE_SIZE 4096

extern char end;

struct blk_allocator allocator;

void allocator_init(void)
{
    void *end_ptr = &end;
    unsigned int end_ptr_u32 = (unsigned int)end_ptr;
    end_ptr_u32 = end_ptr_u32 - end_ptr_u32 % PAGE_SIZE + PAGE_SIZE;
    end_ptr = (void *)end_ptr_u32;
    allocator.head = end_ptr;

    allocator.head->size = PAGE_SIZE - sizeof(struct blk_meta);
    allocator.head->next = NULL;
    allocator.head->prev = NULL;
    allocator.head->is_free = 1;
    allocator.end = (char *)(allocator.head) + PAGE_SIZE;
}

struct blk_meta *first_fit(size_t size)
{
    for (struct blk_meta *i = allocator.head; i != NULL; i = i->next)
    {
        if (i->is_free && i->size >= size)
        {
            return i;
        }
    }
    return NULL;
}

void alloc_blk(struct blk_meta *blk, size_t size)
{
    struct blk_meta *new = (struct blk_meta *)((char *)(blk->data) + size);

    new->size = blk->size - size - sizeof(struct blk_meta);
    new->is_free = 1;
    new->prev = blk;
    new->next = blk->next;

    blk->next = new;
    blk->is_free = 0;
    blk->size = size;
}

struct blk_meta *allocator_expand(void)
{
    struct blk_meta *tail = allocator.head;

    while (tail->next)
    {
        tail = tail->next;
    }

    struct blk_meta *new = (struct blk_meta *)allocator.end;
    new->next = NULL;
    new->prev = tail;
    tail->next = new;
    new->is_free = 1;
    new->size = PAGE_SIZE - sizeof(struct blk_meta);
    allocator.end += PAGE_SIZE;

    return new;
}

void *blk_alloc(size_t size)
{
    if (!allocator.head)
    {
        allocator_init();
    }

    struct blk_meta *ff = first_fit(size);

    if (!ff)
    {
        ff = allocator_expand();
    }

    alloc_blk(ff, size);
    return ff->data;
}

void merge_free_prev(struct blk_meta *blk)
{
    if (blk->prev && blk->prev->is_free)
    {
        merge_free_prev(blk->prev);
        blk->prev->size = blk->prev->size + sizeof(struct blk_meta) + blk->size;
        blk->prev->next = blk->next;
    }
}

void merge_free_next(struct blk_meta *blk)
{
    if (blk->next && blk->next->is_free)
    {
        merge_free_next(blk->next);
        blk->size = blk->size + sizeof(struct blk_meta) + blk->next->size;
        blk->next = blk->next->next;
    }
}

void blk_free(void *ptr)
{
    unsigned int int_ptr = (unsigned int)ptr;
    int_ptr -= sizeof(struct blk_meta);
    ptr = (void *)int_ptr;
    struct blk_meta *blk = ptr;

    blk->is_free = 1;
    merge_free_prev(blk);
    merge_free_next(blk);
}
