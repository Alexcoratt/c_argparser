#include <stdlib.h>
#include "common.h"

void defaultDelete(void *ptr) {
    free(ptr);
}