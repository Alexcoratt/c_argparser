#include <stdlib.h>

#include "argparser.h"
#include "common.h"
#include "hashmap.h"

// struct ParseResult methods' definitions
void initParsingResult(struct ParsingResult *pres) {
    queue_init(&pres->args, (alloc_func)allocString, NULL);
    queue_init(&pres->flags, (alloc_func)allocString, NULL);
    hm_init(&pres->params, 8, NULL, (alloc_func)allocString, NULL);
}

void freeParsingResult(struct ParsingResult *pres) {
    queue_free(&pres->args);
    queue_free(&pres->flags);
    hm_free(&pres->params);
}

// struct Config methods' definitions
void initConfig(
    struct Config *conf,
    is_acceptable_arg_count_func acf,

    size_t flagCount,
    char **flags,
    bool *argRequired
) {
    conf->acf = acf;

    hm_init(&conf->argRequired, flagCount, NULL, (alloc_func)allocBool, NULL);
    for (size_t i = 0; i < flagCount; ++i)
        hm_set(&conf->argRequired, flags[i], argRequired + i);
}

void freeConfing(struct Config *conf) {
    hm_free(&conf->argRequired);
}

bool *allocBool(bool *val) {
    bool *res = T_MALLOC(bool);
    if (val)
        *res = *val;
    return res;
}

// Used for setting argument of a flag (if it takes one)
static enum Status processFlag(const struct Hashmap *config, struct ParsingResult *pres, const char **keyToAssign, const char *key) {
    bool **hasArg = (bool **)hm_get(config, key);
    if (!hasArg || !*hasArg)
        return STATUS_WRONG_FLAG;

    if (**hasArg)
        *keyToAssign = key;
    else
        queue_push(&pres->flags, key);

    return STATUS_SUCCESS;
}

enum Status parseArgs(const struct Config *conf, struct ParsingResult *pres, size_t argc, char **argv) {
    const char *keyToAssign = NULL;
    for (size_t i = 0; i < argc; ++i) {
        char *arg = argv[i];

        if (keyToAssign) {
            hm_set(&pres->params, keyToAssign, arg);
            keyToAssign = NULL;
        } else if (arg[0] == '-') {
            if (arg[1] == '-') {
                enum Status s = processFlag(&conf->argRequired, pres, &keyToAssign, arg + 2);
                if (s != STATUS_SUCCESS)
                    return s;
            } else {
                for (char *flag = arg + 1; *flag; ++flag) {
                    char flag_str[] = {*flag, '\0'};
                    enum Status s = processFlag(&conf->argRequired, pres, &keyToAssign, flag_str);
                    if (s != STATUS_SUCCESS)
                        return s;
                }
            }
        } else
            queue_push(&pres->args, arg);
    }

    if (keyToAssign)
        return STATUS_NO_FLAG_ARGUMENT;

    if (!conf->acf(queue_size(&pres->args)))
        return STATUS_WRONG_ARGUMENT_COUNT;

    return STATUS_SUCCESS;
}