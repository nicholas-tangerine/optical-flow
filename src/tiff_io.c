#include <stdlib.h>

#include "tiff_io.h"

void freeImg(TIFF **tif) {
    TIFFClose(*tif);
    *tif = NULL;
    return;
}

uint32_t *readTiffToBuffer(TIFF *tif, uint32_t *buffer, uint32_t height, uint32_t width) {
    int res = TIFFReadRGBAImageOriented(tif, width, height, buffer,
            ORIENTATION_TOPLEFT, 0);

    if (res != 1) {
        fprintf(stderr, "DEBUG: error reading TIFF into buffer");
        exit(1);
    }

    return buffer;
}

void getImgDimensions(TIFF *tif, uint32_t *imgHeight, uint32_t *imgWidth) {
    int res1 = TIFFGetField(tif, TIFFTAG_IMAGELENGTH, imgHeight);
    int res2 = TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, imgWidth);

    if (res1 != 1 || res2 != 1) {
        fprintf(stderr, "DEBUG: no width or no height tag in image\n");
        exit(1);
    }

    return;

}
