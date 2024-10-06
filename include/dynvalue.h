#ifndef DYNVALUE_H
#define DYNVALUE_H

#include <stddef.h>
#include "stdbool.h"

enum ValueType {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
};

size_t getTypeSize(enum ValueType);

union __DynValue {
    int int_val;
    double double_val;
    char *string_val;
};

struct DynValue {
    enum ValueType type;
    union __DynValue value;
};

void parseDynValue(struct DynValue *, const char *);

void initDynValue(struct DynValue *, enum ValueType);
void destructDynValue(struct DynValue *);

bool transformDynValue(struct DynValue *dest, const struct DynValue *src);

#endif