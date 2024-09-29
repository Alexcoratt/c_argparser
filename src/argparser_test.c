#include <stdio.h>
#include <string.h>

#include "argparser.h"
#include "hashmap.h"
#include "stack.h"

#define INIT_HASHMAP_CAPACITY 8

void setConfig(struct Hashmap *conf, size_t keyCount, char **keys, bool *hasArgs) {
    for (size_t i = 0; i < keyCount; ++i)
        resetHashmap(conf, strlen(keys[i]), keys[i], hasArgs + i);
}

int main(int argc, char **argv) {
    struct ParseResult pres;
    pres.args = EMPTY_STACK;
    initHashmap(&pres.flagArgs, INIT_HASHMAP_CAPACITY, NULL, NULL);

    char *keys[] = {"help", "t", "u", "cap"};
    bool hasArgs[] = {false, true, false, true};

    struct Hashmap conf;
    initHashmap(&conf, INIT_HASHMAP_CAPACITY, NULL, NULL);
    setConfig(&conf, 4, keys, hasArgs);

    parseArgs(argc, argv, &conf, &pres);

    for (int i = 0; i < 4; ++i) {
        char *value = (char *)getHashmap(&pres.flagArgs, strlen(keys[i]), keys[i]);
        printf("flags[%s] = %s\n", keys[i], value ? value : "NULL");
    }

    for (int i = 0; pres.args; ++i)
        printf("arg #%d = %s\n", i, (char *)popStack(&pres.args));

    destructHashmap(&pres.flagArgs);
    destructHashmap(&conf);

    return 0;
}