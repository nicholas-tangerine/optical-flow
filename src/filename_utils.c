#include "filename_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *get_output_name(char *input_name) {
    char *extension = strrchr(input_name, '.');

    if (strcmp(extension, ".tif") != 0) {
        fprintf(stderr, "DEBUG: unrecognized file, must be .tif\n");
        return "";
    }

    int base_len = (int) (extension - input_name);
    char *suffix = "_processed.tif";

    char *output = calloc((size_t) base_len + (size_t) strlen(suffix) + (size_t) 1,
            sizeof(char));
    if (output == NULL) {
        fprintf(stderr, "DEBUG: couldn't allocate space for new filename\n");
        return "";
    }
    strncpy(output, input_name, (size_t) base_len);
    output[base_len] = '\0';
    strcat(output, suffix);

    return output;
}
