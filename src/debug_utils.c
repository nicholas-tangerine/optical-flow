#include <stdlib.h>
#include <string.h>

#include "tiff_io.h"

void writeBufferToPPM(uint32_t width, uint32_t height, uint32_t *buffer, char *outputFile) {
    if (strcmp(outputFile, "") == 0) outputFile = "output.ppm";

    FILE *fp = fopen(outputFile, "wb");
    if (fp == NULL) {
        fprintf(stderr, "DEBUG: error opening file\n");
        exit(1);
    }

    fprintf(fp, "P6\n%d %d\n%d\n", width , height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width ; x++) {
            int index = y * width + x;
            int bufferVal = buffer[index];

            unsigned int r = (unsigned int)(0xff&(bufferVal >> 24));
            unsigned int g = (unsigned int)(0xff&(bufferVal >> 16));
            unsigned int b = (unsigned int)(0xff&(bufferVal >> 8));
            unsigned int a = (unsigned int)(0xff&(bufferVal >> 0));

            unsigned int avg = (r + g + b + a) >> 2;    // divide by 4 to get
                                                        // avg

            fputc(avg, fp);
            fputc(avg, fp);
            fputc(avg, fp);
        }
    }

    return;
}
