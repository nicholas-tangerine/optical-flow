#include "filename_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *get_output_name(char *input_name) {
    char *extension = strrchr(input_name, '.');

    if (strcmp(extension, ".tif") != 0) {
        fprintf(stderr, "DEBUG: unrecognized file, must be .tif\n");
        exit(1);
    }

    int base_len = (int) (extension - input_name);
    char *suffix = "_processed.tif";

    char *output = calloc(base_len + (int) strlen(suffix) + 1,
            sizeof(char));
    if (output == NULL) {
        fprintf(stderr, "DEBUG: couldn't allocate space for new filename\n");
        exit(1);
    }
    strncpy(output, input_name, base_len);
    output[base_len] = '\0';
    strcat(output, suffix);

    return output;
}
