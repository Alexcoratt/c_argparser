#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <stddef.h>

#define T_MALLOC(TYPE) (TYPE *)malloc(sizeof(TYPE))
#define T_CALLOC(TYPE, COUNT) (TYPE *)calloc(COUNT, sizeof(TYPE))

typedef void *alloc_func(size_t typeSize);
typedef void delete_func(void *);

alloc_func defaultAlloc;
delete_func defaultDelete;

#endif