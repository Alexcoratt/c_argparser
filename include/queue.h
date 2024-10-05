#ifndef QUEUE_H
#define QUEUE_H

#include "simple_stack.h"
#include "common.h"

struct Queue {
    sstack first;   // first to go out
    sstack last;    // last went in

    alloc_func alloc;
    del_func del;
};

void queue_init(struct Queue *, alloc_func, del_func);
void queue_free(struct Queue *);

void queue_push(struct Queue *, const void *value);
void *queue_pop(struct Queue *);

size_t queue_size(const struct Queue *);
bool is_queue_empty(const struct Queue *);

// auxillary functions
void queue_traverse(const struct Queue *, sstack_traverse_func);

#endif