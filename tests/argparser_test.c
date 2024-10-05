#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "common.h"
#include "hashmap.h"

bool *allocBool(bool *val) {
    bool *res = T_MALLOC(bool);
    if (val)
        *res = *val;
    return res;
}

struct Hashmap mkConfig(size_t keyCount, const char **keys, const bool *hasArgs) {
    struct Hashmap conf;
    hm_init(&conf, keyCount, NULL, (alloc_func)allocBool, NULL);
    for (size_t i = 0; i < keyCount; ++i)
        hm_set(&conf, keys[i], hasArgs + i);
    return conf;
}

int counter = 0;
void printIndexString(const char *str) {
    printf("\tvalue #%d = %s\n", counter++, str);
}

void printStringPair(const char *key, const char *value) {
    printf("\t[%s] = %s\n", key, value);
}

int main(int argc, char **argv) {
    struct ParseResult pres;
    initParseResults(&pres);

    const char *keys[] = {"help", "t", "u", "cap"};
    const bool hasArgs[] = {false, true, false, true};

    struct Hashmap conf = mkConfig(4, keys, hasArgs);
    enum Status s = parseArgs(argc, argv, &conf, &pres);
    hm_free(&conf);

    if (s != STATUS_SUCCESS) {
        fprintf(stderr, "Error occured while processing flags. Error code: %d\n", s);
        freeParseResults(&pres);
        return s;
    }

    puts("args:");
    queue_traverse(&pres.args, (sstack_traverse_func)printIndexString);

    puts("\nflags:");
    queue_traverse(&pres.flags, (sstack_traverse_func)printIndexString);

    puts("\nparams:");
    hm_traverse(&pres.params, (hm_traverse_func)printStringPair);

    freeParseResults(&pres);

    return 0;
}