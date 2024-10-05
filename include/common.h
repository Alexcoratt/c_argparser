#ifndef BASIC_DEF_H
#define BASIC_DEF_H

#include <stddef.h>

#define T_MALLOC(TYPE) (TYPE *)malloc(sizeof(TYPE))
#define T_CALLOC(TYPE, COUNT) (TYPE *)calloc(COUNT, sizeof(TYPE))

// value is an optional parameter
// if set the function returns a pointer
// to the copy of given value
typedef void *(*alloc_func)(const void *value);
typedef void (*del_func)(void *);

void defaultDel(void *value);

// auxillary methods
char *allocString(const char *);

#endif