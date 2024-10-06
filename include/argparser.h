#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stddef.h>

#include "hashmap.h"
#include "queue.h"

enum Status {
    STATUS_SUCCESS = 0,
    STATUS_UNKNOWN_ERROR,

    STATUS_WRONG_FLAG,
    STATUS_NO_FLAG_ARGUMENT,
    STATUS_CONFLICTING_FLAGS,
    STATUS_WRONG_ARGUMENT_COUNT
};

struct ParsingResult {
    struct Queue args; // queue of char *
    struct Queue flags; // queue of char *
    struct Hashmap params;
};

void initParsingResult(struct ParsingResult *);
void freeParsingResult(struct ParsingResult *);

bool *allocBool(bool *val);

// config has to be initialized before calling setConfig
// sets config's allocator to allocBool and deleter to defaultDel
// also fills config with given flags and bool flags
void setConfig(struct Hashmap *config, size_t flagCount, char **flags, bool *argRequired);
/* 
 * config has to be a hashmap where keys are flags
 * and values are bools containing if the flag takes
 * an argument
 */

enum Status parseArgs(const struct Hashmap *conf, struct ParsingResult *pres, size_t argc, char **argv);

#endif