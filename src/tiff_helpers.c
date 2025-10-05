#include <stdlib.h>

#include "tiff_helpers.h"


void readTIFFToBuffer(TIFF *tif, uint32_t *buffer, uint32_t height, uint32_t width) {
    int res = TIFFReadRGBAImageOriented(tif, width, height, buffer,
            ORIENTATION_TOPLEFT, 0);

    if (res != 1) {
        fprintf(stderr, "DEBUG: error reading TIFF into buffer");
        exit(1);
    }
}

uint32_t getTIFFHeight(TIFF *tif) {
    uint32_t height;

    int res = TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

    if (res == 1) return height;

    fprintf(stderr, "DEBUG: couldn't get TIFF height\n");
    exit(1);

    return height;
}

uint32_t getTIFFWidth(TIFF *tif) {
    uint32_t width;

    int res = TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);

    if (res == 1) return width;

    fprintf(stderr, "DEBUG: couldn't get TIFF width\n");
    exit(1);

    return width;
}
