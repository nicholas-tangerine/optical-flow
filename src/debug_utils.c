#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tiff_helpers.h"
#include "debug_utils.h"

void write_color_buffer_to_ppm(uint32_t *buffer, uint32_t width, uint32_t height, char *output_file) {
    if (strcmp(output_file, "") == 0) output_file = "output.ppm";

    FILE *fp = fopen(output_file, "wb");
    if (fp == NULL) {
        fprintf(stderr, "DEBUG: error opening file\n");
        return;
    }

    fprintf(fp, "P6\n%d %d\n%d\n", width , height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width ; x++) {
            uint32_t index = y * width + x;
            uint32_t buffer_val = buffer[index];

            unsigned int r = TIFFGetR(buffer_val);
            unsigned int g = TIFFGetG(buffer_val);
            unsigned int b = TIFFGetB(buffer_val);
            unsigned int a = TIFFGetA(buffer_val);

            float alpha = (float) a / 255.0f;        //  scaled between 0 and 1

            r = (unsigned int) ((float) r * alpha);
            g = (unsigned int) ((float) g * alpha);
            b = (unsigned int) ((float) b * alpha);

            fputc((int) r, fp);
            fputc((int) g, fp);
            fputc((int) b, fp);
        }
    }

    fclose(fp);
    fp = NULL;

    return;
}

void write_intensity_buffer_to_ppm(image_t *image, char *output_file) {
    if (strcmp(output_file, "") == 0) output_file = "output.ppm";

    float *buffer = image->intensity_buffer;
    uint32_t width = image->width;
    uint32_t height = image->height;

    FILE *fp = fopen(output_file, "wb");
    if (fp == NULL) {
        fprintf(stderr, "DEBUG: error opening file\n");
        return;
    }

    fprintf(fp, "P5\n%d %d\n%d\n", width , height, 255);
    
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width ; x++) {
            uint32_t index = y * width + x;
            float buffer_val = buffer[index];

            unsigned char intensity = (unsigned char) (buffer_val * 255.0f);

            fputc(intensity, fp);
        }
    }

    fclose(fp);
    fp = NULL;

    return;
}
