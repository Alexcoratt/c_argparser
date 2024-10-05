#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

#include <stddef.h>
#include <stdbool.h>

struct SingleList {
    void *value;
    struct SingleList *next;
};

struct SingleList *initSingleListPtr(void *value, struct SingleList *next);
void freeSingleList(struct SingleList *);

typedef struct SingleList *sstack; // simple stack

#define EMPTY_SSTACK NULL // if sstack == EMPTY_SSTACK then sstack is empty

void sstack_push(sstack*, void *value);
void *sstack_pop(sstack*);

size_t sstack_size(sstack);

// auxillary methods
typedef void (*sstack_traverse_func)(void *);
void sstack_traverse(sstack, sstack_traverse_func);

typedef bool (*eq_func)(const void *, const void *);
sstack *sstack_find(sstack, const void *example, eq_func);

#endif