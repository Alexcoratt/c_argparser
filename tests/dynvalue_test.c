#include "dynvalue.h"
#include "print_dynvalue.h"

int main(int argc, char **argv) {
    struct DynValue dval;
    initDynValue(&dval, TYPE_DOUBLE);
    dval.value.double_val = 3.0;
    printDynValue(&dval, "\n");
    destructDynValue(&dval);

    struct DynValue dval2;
    initDynValue(&dval2, TYPE_STRING);
    transformDynValue(&dval2, &dval);
    printDynValue(&dval2, "\n");
    destructDynValue(&dval2);

    return 0;
}