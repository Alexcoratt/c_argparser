#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stddef.h>

#include "hashmap.h"
#include "stack.h"

enum Status {
    STATUS_SUCCESS,

    STATUS_UNKNOWN_ERROR,
    STATUS_WRONG_FLAG,
    STATUS_NO_FLAG_ARGUMENT
};

struct ParseResult {
    stack args; // stack of char * (taken from argv)
    struct Hashmap flagArgs; // flag arguments (keys and values are taken from argv)
};

/* <config> has to be a hashmap where keys are flags
 * and values are bools containing if the flag takes
 * an argument
 */
enum Status parseArgs(size_t argc, char **argv, const struct Hashmap *config, struct ParseResult *pres);

#endif