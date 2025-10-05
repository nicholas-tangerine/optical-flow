#include <stdlib.h>

#include "tiff_io.h"
#include "preprocessor.h"

#include "debug_utils.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        exit(1);
    }

    TIFF *imgBefore = openImg(argv[1], "r");
    TIFF *imgAfter = openImg(argv[2], "r");

    uint32_t *bufferBefore = readTiffToBuffer(imgBefore);
    uint32_t *bufferAfter = readTiffToBuffer(imgAfter);

    uint32_t *imgDimensionsBefore = calloc(2, sizeof(uint32_t));
    uint32_t *imgDimensionsAfter= calloc(2, sizeof(uint32_t));

    getImgDimensions(imgBefore, imgDimensionsBefore);
    getImgDimensions(imgAfter, imgDimensionsAfter);

    if (imgDimensionsBefore[0] != imgDimensionsAfter[0] || imgDimensionsBefore[1] != imgDimensionsAfter[1]) {
        fprintf(stderr, "DEBUG: before and after images do not have the same dimensions");
        exit(1);
    }

    uint32_t height = imgDimensionsBefore[0];
    uint32_t width = imgDimensionsBefore[1];

    writeBufferToPPM(width, height, bufferBefore, "output1.ppm");
    writeBufferToPPM(width, height, bufferAfter, "output2.ppm");

    /**
     * FREE MEMORY
     */
    free(bufferBefore);
    free(bufferAfter);

    freeImg(&imgBefore);
    freeImg(&imgAfter);

    return 0;
}
