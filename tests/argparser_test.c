#include <stdio.h>

#include "argparser.h"
#include "hashmap.h"

int counter = 0;
void printIndexString(const char *str) {
    printf("\tvalue #%d = %s\n", counter++, str);
}

void printStringPair(const char *key, const char *value) {
    printf("\t[%s] = %s\n", key, value);
}

bool isAcceptableArgCount(size_t argCount) {
    return argCount < 4;
}

int main(int argc, char **argv) {
    struct ParsingResult pres;
    initParsingResult(&pres);

    char *keys[] = {"help", "t", "u", "cap"};
    bool argRequired[] = {false, true, false, true};

    struct Config conf;
    initConfig(&conf, isAcceptableArgCount, 4, keys, argRequired);
    enum Status s = parseArgs(&conf, &pres, argc, argv);
    freeConfing(&conf);

    if (s != STATUS_SUCCESS) {
        fprintf(stderr, "Error occured while processing flags. Error code: %d\n", s);
        freeParsingResult(&pres);
        return s;
    }

    puts("args:");
    queue_traverse(&pres.args, (sstack_traverse_func)printIndexString);

    puts("\nflags:");
    counter = 0;
    queue_traverse(&pres.flags, (sstack_traverse_func)printIndexString);

    puts("\nparams:");
    hm_traverse(&pres.params, (hm_traverse_func)printStringPair);

    freeParsingResult(&pres);

    return 0;
}