#include "filename_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *getOutputName(char *inputName) {
    char *extension = strrchr(inputName, '.');

    if (strcmp(extension, ".tif") != 0) {
        fprintf(stderr, "DEBUG: unrecognized file, must be .tif\n");
        exit(1);
    }

    int baseLen = (int) (extension - inputName);
    char *suffix = "_processed.tif";

    char *output = calloc(baseLen + (int) strlen(suffix) + 1,
            sizeof(char));
    if (output == NULL) {
        fprintf(stderr, "DEBUG: couldn't allocate space for new filename\n");
        exit(1);
    }
    strncpy(output, inputName, baseLen);
    output[baseLen] = '\0';
    strcat(output, suffix);

    return output;
}
