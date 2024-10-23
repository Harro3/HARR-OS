#ifndef MEMORY_H
#define MEMORY_H

#include "stdlib/def.h"

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif
