#include <string.h>

#include "argparser.h"
#include "common.h"

// struct ParseResult methods' definitions
void initParseResults(struct ParseResult *pres) {
    queue_init(&pres->args, (alloc_func)allocString, NULL);
    queue_init(&pres->flags, (alloc_func)allocString, NULL);
    hm_init(&pres->params, 8, NULL, (alloc_func)allocString, NULL);
}

void freeParseResults(struct ParseResult *pres) {
    queue_free(&pres->args);
    queue_free(&pres->flags);
    hm_free(&pres->params);
}

// Used for setting argument of a flag (if it takes one)
static enum Status processFlag(const struct Hashmap *config, struct ParseResult *pres, const char **keyToAssign, const char *key) {
    bool **hasArg = (bool **)hm_get(config, key);
    if (!hasArg || !*hasArg)
        return STATUS_WRONG_FLAG;

    if (**hasArg)
        *keyToAssign = key;
    else
        queue_push(&pres->flags, key);

    return STATUS_SUCCESS;
}

enum Status parseArgs(size_t argc, char **argv, const struct Hashmap *config, struct ParseResult *pres) {
    const char *keyToAssign = NULL;
    for (size_t i = 0; i < argc; ++i) {
        char *arg = argv[i];

        if (keyToAssign) {
            hm_set(&pres->params, keyToAssign, arg);
            keyToAssign = NULL;
        } else if (arg[0] == '-') {
            if (arg[1] == '-') {
                enum Status s = processFlag(config, pres, &keyToAssign, arg + 2);
                if (s != STATUS_SUCCESS)
                    return s;
            } else {
                for (char *flag = arg + 1; *flag; ++flag) {
                    char flag_str[] = {*flag, '\0'};
                    enum Status s = processFlag(config, pres, &keyToAssign, flag_str);
                    if (s != STATUS_SUCCESS)
                        return s;
                }
            }
        } else
            queue_push(&pres->args, arg);
    }

    if (keyToAssign)
        return STATUS_NO_FLAG_ARGUMENT;

    return STATUS_SUCCESS;
}