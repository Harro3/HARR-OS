#ifndef STRING_H
#define STRING_H

#include "def.h"

void *memmove(void *dest, const void *src, size_t n);
void itoa(int n, char *res);
int atoi(char *str);

int strcmp(char *a, char *b);

#endif
