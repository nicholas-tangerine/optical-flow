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
    //TIFF *imgAfter = openImg(argv[2], "w");

    uint32_t *bufferBefore = readTiffToBuffer(imgBefore);

    /**
     * start random stuff
     */
    uint32_t *imgDimensions = calloc(2, sizeof(uint32_t));
    getImgDimensions(imgBefore, imgDimensions);

    uint32_t height = imgDimensions[0];
    uint32_t width = imgDimensions[1];

    writeBufferToPPM(width, height, bufferBefore, "");
    /**
     * end random stuff
     */


    free(bufferBefore);

    /**
     * FREE MEMORY
     */
    freeImg(&imgBefore);
    //freeImg(&imgAfter);


    return 0;
}
