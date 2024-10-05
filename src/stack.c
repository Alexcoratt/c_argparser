#include "stack.h"

void stack_init(struct Stack *st, alloc_func alloc, del_func del) {
    st->first = EMPTY_SSTACK;
    st->alloc = alloc;
    st->del = del ? del : defaultDel;
}

void stack_free(struct Stack *st) {
    while (st->first != EMPTY_SSTACK)
        st->del(sstack_pop(&st->first));
}

void stack_push(struct Stack *st, const void *value) {
    sstack_push(&st->first, st->alloc(value));
}

void *stack_pop(struct Stack *st) {
    return sstack_pop(&st->first);
}

size_t stack_size(const struct Stack *st) {
    return sstack_size(st->first);
}

bool is_stack_empty(const struct Stack *st) {
    return st->first == EMPTY_SSTACK;
}

// auxillary functions
void stack_traverse(struct Stack *st, sstack_traverse_func func) {
    sstack_traverse(st->first, func);
}