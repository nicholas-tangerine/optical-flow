#include <stdlib.h>

#include "tiff_io.h"

void freeImg(TIFF **tif) {
    TIFFClose(*tif);
    *tif = NULL;
    return;
}

void getImgDimensions(TIFF *tif, int *imgDimensions) {
    uint32_t height;
    uint32_t width;

    int res1 = TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
    int res2 = TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);

    if (res1 != 1 || res2 != 1) {
        fprintf(stderr, "DEBUG: no length or no width tab\n");
        exit(1);
    }

    imgDimensions[0] = (int) height;
    imgDimensions[1] = (int) width;

    return;

}
