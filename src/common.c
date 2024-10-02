#include <stdlib.h>
#include "common.h"

void *defaultAlloc(size_t typeSize) {
    return malloc(typeSize);
}

void defaultDelete(void *ptr) {
    free(ptr);
}