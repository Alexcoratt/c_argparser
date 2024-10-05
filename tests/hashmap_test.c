#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "hashmap.h"

int *allocInt(const int *value) {
    if (!value)
        return malloc(sizeof(int));

    int *res = T_MALLOC(int);
    *res = *value;
    return res;
}

void printKeyValue(char *key, void *value) {
    printf("map[%s] = %d\n", key, *(int *)value);
}

int main(int argc, char **argv) {
    struct Hashmap map;
    hm_init(&map, 8, NULL, (alloc_func)allocInt, NULL);

    for (int i = 0; i < argc; ++i)
        hm_set(&map, argv[i], &i);

    hm_traverse(&map, printKeyValue);
    hm_free(&map);

    return 0;
}