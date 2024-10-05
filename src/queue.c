#include "queue.h"

void queue_init(struct Queue *q, alloc_func alloc, del_func del) {
    q->last = q->first = NULL;
    q->alloc = alloc;
    q->del = del ? del : defaultDel;
}

void queue_free(struct Queue *q) {
    while (q->first != EMPTY_SSTACK)
        q->del(sstack_pop(&q->first));
}

void queue_push(struct Queue *q, const void *value) {
    sstack newItem = initSingleListPtr(q->alloc(value), NULL);
    if (q->first == EMPTY_SSTACK)
        q->first = q->last = newItem;
    else
        q->last = q->last->next = newItem;
}

void *queue_pop(struct Queue *q) {
    if (q->first == q->last)
        q->last = EMPTY_SSTACK;
    return sstack_pop(&q->first);
}

size_t queue_size(const struct Queue *q) {
    return sstack_size(q->first);
}

bool is_queue_empty(const struct Queue *q) {
    return q->first == EMPTY_SSTACK;
}

void queue_traverse(const struct Queue *q, sstack_traverse_func func) {
    sstack_traverse(q->first, func);
}