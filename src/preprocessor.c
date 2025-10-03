#include <stdlib.h>
#include <string.h>

#include "preprocessor.h"

Preprocessor *createPreprocessor(char *fileNameIn) {
    char *fileNameOut = getOutputName(fileNameIn);

    Preprocessor *preprocessor = calloc(1, sizeof(Preprocessor));

    preprocessor->imgFileIn = TIFFOpen(fileNameIn, "r");
    preprocessor->imgFileOut = TIFFOpen(fileNameOut, "w");

    return preprocessor;
}

void deletePrepreprocessor(Preprocessor **preprocessor) {
    free(*preprocessor);
    *preprocessor = NULL;
}

void *getTags(Preprocessor *preprocessor, int tag) {
    uint32_t count;
    void *data;
    int res = TIFFGetField(preprocessor->imgFileIn, tag, &count, &data);

    if (res != 1) {
        fprintf(stderr, "DEBUG: could not get TIFF tag");
        exit(1);
    }

    return data;
}

void printAllTags(Preprocessor *preprocessor) {
}

char *getOutputName(char *fileName) {
    char *extension = strrchr(fileName, '.');

    if (strcmp(extension, ".tif") != 0) {
        printf("DEBUG: unrecognized file, must be .tif\n");
        exit(1);
    }

    int baseLen = (int) (extension - fileName);
    char *suffix = "_processed.tif";

    char *output = calloc(baseLen + (int) strlen(suffix) + 1, sizeof(char));
    strncpy(output, fileName, baseLen);
    output[baseLen] = '\0';
    strcat(output, suffix);

    return output;
}
