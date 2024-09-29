#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct __Singlist {
    void *value;
    struct __Singlist *next;
};

typedef struct __Singlist *stack;

#define EMPTY_STACK NULL

void pushStack(stack *, void *value);
void *popStack(stack *);

size_t sizeStack(stack);

#endif