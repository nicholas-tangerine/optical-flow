#include <stdlib.h>

#include "tiff_io.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        exit(1);
    }

    TIFF *imgBefore = openImg(argv[1], "r");
    //TIFF *imgAfter = openImg(argv[2], "w");
    
    int *imgDimensions = calloc(2, sizeof(int));
    getImgDimensions(imgBefore, imgDimensions);

    printf("%d %d\n", imgDimensions[0], imgDimensions[1]);

    /**
     * FREE MEMORY
     */
    freeImg(&imgBefore);
    //freeImg(&imgAfter);
    free(imgDimensions);
    imgDimensions = NULL;

    return 0;
}
