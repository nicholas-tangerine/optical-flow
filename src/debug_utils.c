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

            unsigned int r = TIFFGetR(bufferVal);
            unsigned int g = TIFFGetG(bufferVal);
            unsigned int b = TIFFGetB(bufferVal);
            unsigned int a = TIFFGetA(bufferVal);

            float alpha = a / 256.0;

            r = (unsigned int) (r * alpha);
            g = (unsigned int) (g * alpha);
            b = (unsigned int) (b * alpha);

            fputc(r, fp);
            fputc(g, fp);
            fputc(b, fp);
        }
    }

    fclose(fp);
    fp = NULL;

    return;
}
