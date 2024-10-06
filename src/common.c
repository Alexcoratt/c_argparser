#include <stdlib.h>
#include <string.h>
#include "common.h"

void defaultDel(void *ptr) {
    free(ptr);
}

char *allocString(const char *str) {
    if (str)
        return strcpy(malloc(strlen(str) + 1 * sizeof(char)), str);
    return calloc(1, sizeof(char));
}

void freeString(char *str) {
    free(str);
}

bool eqStrings(const char *left, const char *right) {
    for (size_t i = 0; left[i] || right[i]; ++i)
        if (left[i] != right[i])
            return false;
    return true;
}