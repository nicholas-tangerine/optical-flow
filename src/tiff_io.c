#include <stdlib.h>

#include "tiff_io.h"

void freeImg(TIFF **tif) {
    TIFFClose(*tif);
    *tif = NULL;
    return;
}

uint32_t *readTiffToBuffer(TIFF *tif) {
    uint32_t *imgDimensions = calloc(2, sizeof(int));
    getImgDimensions(tif, imgDimensions);

    uint32_t height = imgDimensions[0];
    uint32_t width = imgDimensions[1];

    uint32_t *buffer = (uint32_t *) calloc(height * width, sizeof(uint32_t));

    int res = TIFFReadRGBAImageOriented(tif, width, height, buffer,
            ORIENTATION_TOPLEFT, 0);

    if (res != 1) {
        fprintf(stderr, "DEBUG: error reading TIFF into buffer");
        exit(1);
    }
    
    free(imgDimensions);
    return buffer;
}

void getImgDimensions(TIFF *tif, uint32_t *imgDimensions) {
    uint32_t height;
    uint32_t width;

    int res1 = TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
    int res2 = TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);

    if (res1 != 1 || res2 != 1) {
        fprintf(stderr, "DEBUG: no widthor no width tab\n");
        exit(1);
    }

    imgDimensions[0] = height;
    imgDimensions[1] = width;

    return;

}
