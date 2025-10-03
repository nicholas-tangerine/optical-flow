#include <stdlib.h>

#include "tiff_io.h"
#include "preprocessor.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        exit(1);
    }

    TIFF *imgBefore = openImg(argv[1], "r");
    //TIFF *imgAfter = openImg(argv[2], "w");

    int *bufferBefore = readTiffToBuffer(imgBefore);

    /**
     * start random stuff
     */
    int *imgDimensions = calloc(2, sizeof(int));

    getImgDimensions(imgBefore, imgDimensions);
    int height = imgDimensions[0];
    int length = imgDimensions[1];

    FILE *fp = fopen("output.ppm", "wb");
    if (fp == NULL) {
        fprintf(stderr, "error opening file\n");
        exit(1);
    }

    fprintf(fp, "P6\n%d %d\n%d\n", length, height, 255);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < length; x++) {
            int index = y * height + x;
            int bufferVal = bufferBefore[index];

            unsigned int r = (unsigned int)(0xff&(bufferVal >> 6));
            unsigned int g = (unsigned int)(0xff&(bufferVal >> 4));
            unsigned int b = (unsigned int)(0xff&(bufferVal >> 2));
            unsigned int a = (unsigned int)(0xff&(bufferVal >> 0));

            unsigned int avg = (r + g + b + a) >> 2;    // divide by 4


            fputc(avg, fp);
            fputc(avg, fp);
            fputc(avg, fp);
        }
    }

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
