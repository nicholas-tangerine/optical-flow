#include <stdlib.h>

#include "tiff_helpers.h"
#include "preprocessor.h"
#include "image.h"

#include "debug_utils.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        exit(1);
    }

    Image *imgBefore = initImage(argv[1], "r");
    Image *imgAfter = initImage(argv[2], "r");

    if (!sameDimensions(imgBefore, imgAfter)) {
        fprintf(stderr, "DEBUG: before and after images do not have the same dimensions\n");
        exit (1);
    }

    writeImageToPPM(imgBefore->width, imgBefore->height, imgBefore->buffer, "output1.ppm");
    writeImageToPPM(imgAfter->width, imgAfter->height, imgAfter->buffer, "output2.ppm");

    freeImage(&imgBefore);
    freeImage(&imgAfter);



    /*
    TIFF *imgBefore = openImg(argv[1], "r");
    TIFF *imgAfter = openImg(argv[2], "r");

    uint32_t imgBeforeHeight, imgBeforeWidth, imgAfterHeight, imgAfterWidth;
    getImgDimensions(imgBefore, &imgBeforeHeight, &imgBeforeWidth);
    getImgDimensions(imgAfter, &imgAfterHeight, &imgAfterWidth);

    if (imgBeforeHeight != imgAfterHeight || imgBeforeWidth != imgAfterWidth) {
        fprintf(stderr, "DEBUG: before and after images do not have the same \
                dimensions");
        exit(1);
    }

    uint32_t height = imgBeforeHeight;
    uint32_t width = imgBeforeWidth;

    uint32_t *bufferBefore = calloc(height * width, sizeof(uint32_t));
    uint32_t *bufferAfter = calloc(height * width, sizeof(uint32_t));

    if (bufferBefore == NULL || bufferAfter == NULL) {
        fprintf(stderr, "DEBUG: could not allocate memory for image buffers\n");
        exit(1);
    }

    readTiffToBuffer(imgBefore, bufferBefore, height, width);
    readTiffToBuffer(imgAfter, bufferAfter, height, width);

    writeBufferToPPM(width, height, bufferBefore, "output1.ppm");
    writeBufferToPPM(width, height, bufferAfter, "output2.ppm");*/

    /**
     * FREE MEMORY
     */

    /*
    free(bufferBefore);
    free(bufferAfter);

    freeImg(&imgBefore);
    freeImg(&imgAfter);*/

    return 0;
}
