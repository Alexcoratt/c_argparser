#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char **argv) {
    struct Hashmap map;
    initHashmap(&map, 8, NULL, NULL);

    int *values = malloc(argc * sizeof(int));

    for (int i = 0; i < argc; ++i) {
        values[i] = i;
        resetHashmap(&map, strlen(argv[i]), argv[i], values + i);
        printf("map size: %lu\n", map.size);
    }

    for (int i = 0; i < argc; ++i) {
        int *value = (int *)getHashmap(&map, strlen(argv[i]), argv[i]);
        if (value)
            printf("map[\"%s\"] = %d\n", argv[i], *value);
        else
            printf("map[\"%s\"] = NULL\n", argv[i]);
    }

    destructHashmap(&map);
    free(values);

    return 0;
}