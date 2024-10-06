#ifndef PRINT_DYNVALUE_H
#define PRINT_DYNVALUE_H

#include <stdio.h>
#include "dynvalue.h"

void printDynValue(const struct DynValue *, const char *endl);
void fprintDynValue(FILE *, const struct DynValue *, const char *endl);

#endif