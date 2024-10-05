#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "hashmap.h"

char *allocString(const char *str) {
    if (!str)
        return NULL;
    return strcpy(malloc((strlen(str) + 1) * sizeof(char)), str);
}

int *allocInt(const int *value) {
    if (!value)
        return malloc(sizeof(int));

    int *res = T_MALLOC(int);
    *res = *value;
    return res;
}

void printKeyValue(size_t keySize, char *key, void *value) {
    printf("map[%s] = %d\n", key, *(int *)value);
}

int main(int argc, char **argv) {
    struct Hashmap map;
    initHashmap(&map, 8, NULL, (alloc_func *)&allocInt, NULL);

    for (int i = 0; i < argc; ++i)
        resetHashmap(&map, strlen(argv[i]), argv[i], &i);

    traverseHashmap(&map, &printKeyValue);
    destructHashmap(&map);

    return 0;
}