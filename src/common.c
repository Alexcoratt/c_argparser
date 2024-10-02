#include <stdlib.h>
#include <string.h>
#include "common.h"

void defaultDelete(void *ptr) {
    free(ptr);
}

char *allocString(const char *str) {
    if (str)
        return strcpy(malloc(strlen(str) + 1 * sizeof(char)), str);
    return calloc(1, sizeof(char));
}