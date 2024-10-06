#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dynvalue.h"

size_t getTypeSize(enum ValueType type) {
    switch (type) {
        case TYPE_INT:
            return sizeof(int);
        case TYPE_DOUBLE:
            return sizeof(double);
        case TYPE_STRING:
            return sizeof(char *);
    }

    return 0;
}

void initDynValue(struct DynValue *dval, enum ValueType type) {
    dval->type = type;
    switch (type) {
        case TYPE_INT:
            dval->value.int_val = 0;
            break;
        case TYPE_DOUBLE:
            dval->value.double_val = 0.0;
            break;
        case TYPE_STRING:
            dval->value.string_val = calloc(1, sizeof(char));
            break;
    }
}

void destructDynValue(struct DynValue *dval) {
    if (dval->type == TYPE_STRING)
        free(dval->value.string_val);
}

int intDigitCount(int value) {
    return (int)(ceil(log10(value))*sizeof(char));
}

#define DOUBLE_DIGIT_COUNT 64;

bool transformDynValue(struct DynValue *dest, const struct DynValue *src) {
    if (dest->type == src->type) {
        if (dest->type == TYPE_STRING)
            strcpy(dest->value.string_val, src->value.string_val);
        else
            memcpy(&dest->value, &src->value, getTypeSize(dest->type));

        return true;
    }

    switch (dest->type) {
        case TYPE_INT:
            switch (src->type) {
                case TYPE_DOUBLE:
                    dest->value.int_val = src->value.double_val;
                    return true;
                case TYPE_STRING: {
                    char *endptr = NULL;
                    long res = strtol(src->value.string_val, &endptr, 0);
                    if (endptr)
                        return false;
                    dest->value.int_val = res;
                    return true;
                } default:
                    return false;
            }
            break;

        case TYPE_DOUBLE:
            switch (src->type) {
                case TYPE_INT:
                    dest->value.double_val = src->value.int_val;
                    return true;
                case TYPE_STRING: {
                    char *endptr = NULL;
                    double res = strtod(src->value.string_val, &endptr);
                    if (endptr)
                        return false;
                    dest->value.double_val = res;
                    return true;
                } default:
                    return false;
            }
            break;

        case TYPE_STRING: {
            char **str = &dest->value.string_val;
            switch (src->type) {
                case TYPE_INT: {
                    const int size = intDigitCount(src->value.int_val) + 1;
                    if (strlen(*str) < size) {
                        free(*str);
                        *str = malloc(size * sizeof(char));
                    }
                    sprintf(*str, "%d", src->value.int_val);
                    return true;
                } case TYPE_DOUBLE: {
                    const int size = DOUBLE_DIGIT_COUNT;
                    if (strlen(*str) < size) {
                        free(*str);
                        *str = malloc(size * sizeof(char));
                    }
                    snprintf(*str, size, "%lf", src->value.double_val);
                    return true;
                } default:
                    return false;
            }
            break;
        }
        
        default:
            return false;
    }
}