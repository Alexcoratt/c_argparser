#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <stddef.h>

#include "hashmap.h"
#include "queue.h"

enum Status {
    STATUS_SUCCESS,
    STATUS_UNKNOWN_ERROR,

    STATUS_WRONG_FLAG,
    STATUS_NO_FLAG_ARGUMENT,
    STATUS_WRONG_ARGUMENT_COUNT
};

struct ParsingResult {
    struct Queue args; // queue of char *
    struct Queue flags; // queue of char *
    struct Hashmap params;
};

void initParsingResult(struct ParsingResult *);
void freeParsingResult(struct ParsingResult *);

typedef bool (*is_acceptable_arg_count_func)(size_t argCount);

struct Config {
    // arg count is normal if true returned
    is_acceptable_arg_count_func acf;

    /* 
    * argRequired has to be a hashmap where keys are flags
    * and values are bools containing if the flag takes
    * an argument
    */
    struct Hashmap argRequired;
};

bool *allocBool(bool *val);

void initConfig(
    struct Config *,
    is_acceptable_arg_count_func acf,

    size_t flagCount,
    char **flags,
    bool *argRequired
);

void freeConfing(struct Config *);

enum Status parseArgs(const struct Config *conf, struct ParsingResult *pres, size_t argc, char **argv);

#endif