#include <stdlib.h>

#include "preprocessor.h"
#include "tiff_io.h"

int *readTiffToBuffer(TIFF *tif) {
    //  allocate buffer
    int *imgDimensions = calloc(2, sizeof(int));
    getImgDimensions(tif, imgDimensions);

    int height = imgDimensions[0];
    int length = imgDimensions[1];

    int *buffer = (int *) calloc(height * length, sizeof(int));

    //  write img data to buffer
    for (int row = 0; row < height; row++) {
        int res = TIFFReadScanline(tif, buffer + height * row, row, 0);
        if (res == 1) continue;

        fprintf(stderr, "Couldn't read scanline on line %d\n", row);
        exit(1);
    }

    free(imgDimensions);
    return buffer;
}

void applyGaussianBlur(TIFF *tif, double sigma) {
    (void) tif;
    (void) sigma;
    return;
}
