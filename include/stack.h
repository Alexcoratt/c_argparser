#ifndef STACK_H
#define STACK_H

#include "simple_stack.h"
#include "common.h"

struct Stack {
    sstack first;

    alloc_func alloc;
    del_func del;
};

void stack_init(struct Stack *, alloc_func, del_func);
void stack_free(struct Stack *);

void stack_push(struct Stack *, const void *value);
void *stack_pop(struct Stack *);

size_t stack_size(const struct Stack *);
bool is_stack_empty(const struct Stack *);

// auxillary functions
void stack_traverse(struct Stack *, sstack_traverse_func);

#endif