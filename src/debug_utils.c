#include <stdlib.h>
#include <string.h>

#include "tiff_helpers.h"

void write_image_to_ppm(uint32_t width, uint32_t height, uint32_t *buffer, char *output_file) {
    if (strcmp(output_file, "") == 0) output_file = "output.ppm";

    FILE *fp = fopen(output_file, "wb");
    if (fp == NULL) {
        fprintf(stderr, "DEBUG: error opening file\n");
        return;
    }

    fprintf(fp, "P6\n%d %d\n%d\n", width , height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width ; x++) {
            int index = y * width + x;
            int buffer_val = buffer[index];

            unsigned int r = TIFFGetR(buffer_val);
            unsigned int g = TIFFGetG(buffer_val);
            unsigned int b = TIFFGetB(buffer_val);
            unsigned int a = TIFFGetA(buffer_val);

            float alpha = a / 255.0;        //  scaled between 0 and 1

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
