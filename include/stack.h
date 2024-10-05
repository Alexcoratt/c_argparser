#ifndef STACK_H
#define STACK_H

#include "single_list.h"
#include "common.h"

struct Stack {
    struct SingleList *first;

    alloc_func *alloc;
    del_func *del;
};

void initStack(struct Stack *, alloc_func *, del_func *);
void destructStack(struct Stack *);

void pushStack(struct Stack *, const void *value);
void *popStack(struct Stack *);

size_t sizeStack(const struct Stack *);
bool isEmptyStack(const struct Stack *);

// auxillary functions
void traverseStack(struct Stack *, single_list_traverse_func *);

#endif