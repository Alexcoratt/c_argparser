#include <stdlib.h>
#include "stack.h"

void pushStack(stack *st, void *value) {
    stack newSt = malloc(sizeof(struct __Singlist));
    newSt->value = value;
    newSt->next = *st;
    *st = newSt;
}

void *popStack(stack *st) {
    void *res = (*st)->value;
    stack next = (*st)->next;
    free(*st);
    *st = next;
    return res;
}

size_t sizeStack(stack st) {
    size_t size = 0;
    for (; st; st = st->next, ++size);
    return size;
}