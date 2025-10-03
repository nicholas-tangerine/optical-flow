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

void getImgDimensions(Preprocessor *preprocessor, int *imgDimensions) {
    uint32_t height;
    uint32_t width;

    int res1 = TIFFGetField(preprocessor->imgFileIn, TIFFTAG_IMAGELENGTH, &height);
    int res2 = TIFFGetField(preprocessor->imgFileIn, TIFFTAG_IMAGEWIDTH, &width);

    if (res1 != 1 || res2 != 1) {
        fprintf(stderr, "DEBUG: could not get TIFF tag\n");
        exit(1);
    }

    imgDimensions[0] = (int) height;
    imgDimensions[1] = (int) width;

    return;
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
