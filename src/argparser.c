#include <string.h>

#include "argparser.h"
#include "hashmap.h"
#include "stack.h"

// Used for setting argument of a flag (if it takes one)
enum Status setFlagValue(const struct Hashmap *config, struct Hashmap *flagArgs, char **keyToAssign, size_t keySize, char *key) {
    bool *hasArgsPtr = (bool *)getHashmap(config, keySize, key);
    if (!hasArgsPtr)
        return STATUS_WRONG_FLAG;

    if (*hasArgsPtr)
        *keyToAssign = key;
    else
        resetHashmap(flagArgs, keySize, key, NULL);

    return STATUS_SUCCESS;
}

enum Status parseArgs(size_t argc, char **argv, const struct Hashmap *config, struct ParseResult *pres) {
    char *keyToAssign = NULL;
    size_t keySize = 0;
    for (size_t i = 0; i < argc; ++i) {
        char *arg = argv[i];

        if (keyToAssign) {
            resetHashmap(&pres->flagArgs, keySize, keyToAssign, arg);
            keyToAssign = NULL;
        } else if (arg[0] == '-') {
            if (arg[1] == '-') {
                keySize = strlen(arg + 2);
                enum Status s = setFlagValue(config, &pres->flagArgs, &keyToAssign, keySize, arg + 2);
                if (s != STATUS_SUCCESS)
                    return s;
            } else {
                keySize = 1;
                for (char *flag = arg + 1; *flag; ++flag) {
                    enum Status s = setFlagValue(config, &pres->flagArgs, &keyToAssign, keySize, flag);
                    if (s != STATUS_SUCCESS)
                        return s;
                }
            }
        } else
            pushStack(&pres->args, arg);
    }

    if (keyToAssign)
        return STATUS_NO_FLAG_ARGUMENT;

    return STATUS_SUCCESS;
}