#include "print_dynvalue.h"
#include "dynvalue.h"
#include <stdio.h>

void printDynValue(const struct DynValue *dval, const char *endl) {
    fprintDynValue(stdout, dval, endl);
}

void fprintDynValue(FILE *ofptr, const struct DynValue *dval, const char *endl) {
    switch (dval->type) {
        case TYPE_INT:
            fprintf(ofptr, "%d%s", dval->value.int_val, endl);
            break;
        case TYPE_DOUBLE:
            fprintf(ofptr, "%lf%s", dval->value.double_val, endl);
            break;
        case TYPE_STRING:
            fprintf(ofptr, "%s%s", dval->value.string_val, endl);
            break;
    }
}