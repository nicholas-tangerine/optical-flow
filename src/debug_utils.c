#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tiff_helpers.h"
#include "math_helper.h"
#include "debug_utils.h"

#include "ofm.h"

void write_color_buffer_to_ppm(image_t *image, char *output_file) {
    uint32_t width = image->width;
    uint32_t height = image->height;
    uint32_t *color_buffer = image->color_buffer;

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
            uint32_t buffer_val = color_buffer[index];

            unsigned int r = TIFFGetR(buffer_val);
            unsigned int g = TIFFGetG(buffer_val);
            unsigned int b = TIFFGetB(buffer_val);
            unsigned int a = TIFFGetA(buffer_val);

            double alpha = (double) a / 255.0f;        //  scaled between 0 and 1

            r = (unsigned int) ((double) r * alpha);
            g = (unsigned int) ((double) g * alpha);
            b = (unsigned int) ((double) b * alpha);

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

    double *buffer = image->intensity_buffer;
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
            double buffer_val = buffer[index];

            unsigned char intensity = (unsigned char) (buffer_val * 255.0f);

            fputc(intensity, fp);
        }
    }

    fclose(fp);
    fp = NULL;

    return;
}

void write_velocity_field_to_file(ofm_t *ofm, char *output_file) {
    if (strcmp(output_file, "") == 0) output_file = "velo_field.txt";
    uint32_t width = ofm->field_width;
    uint32_t height = ofm->field_height;

    double *u_field = ofm->u_field;
    double *v_field = ofm->v_field;

    FILE *fptr = fopen(output_file, "w");
    if (fptr == NULL) {
        fprintf(stderr, "DEBUG: couldn't open velo_field.txt\n");
        height = 0;
        width = 0;
    }

    fprintf(fptr, "%u %u\n", width, height);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int i = get_index(width, height, (int) x, (int) y);
            fprintf(fptr, "%.8f %.8f\n", u_field[i], v_field[i]);
        }
    }

    fclose(fptr);
}
