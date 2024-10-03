#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stddef.h>

#include "hashmap.h"
#include "queue.h"

enum Status {
    STATUS_SUCCESS,

    STATUS_UNKNOWN_ERROR,
    STATUS_WRONG_FLAG,
    STATUS_NO_FLAG_ARGUMENT
};

struct ParseResult {
    struct Queue args; // queue of char *
    struct Queue flags; // queue of char *
    struct Hashmap params;
};

void initParseResults(struct ParseResult *);
void destructParseResults(struct ParseResult *);

/* <config> has to be a hashmap where keys are flags
 * and values are bools containing if the flag takes
 * an argument
 */
enum Status parseArgs(size_t argc, char **argv, const struct Hashmap *config, struct ParseResult *pres);

#endif