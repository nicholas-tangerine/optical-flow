#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tiff_helpers.h"
#include "math_helper.h"
#include "debug_utils.h"

#include "ofm.h"
#include "particle.h"

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

int *draw_streamlines_to_buffer(ofm_t *ofm, uint32_t particle_per_row, uint32_t particle_per_col, uint32_t steps, double dt) {
    uint32_t particles_count = particle_per_row * particle_per_col;

    uint32_t width = ofm->field_width;
    uint32_t height = ofm->field_height;
    uint32_t area = ofm->field_area;

    double *u_field = ofm->u_field;
    double *v_field = ofm->v_field;

    int *buffer = calloc(area, sizeof(int));            //      all values are 0 rn

    particle_t **particles = calloc(particle_per_row * particle_per_col, sizeof(particle_t *));
    uint32_t particles_index = 0;

    uint32_t x_step = width / particle_per_row;
    uint32_t y_step = height / particle_per_col;

    for (uint32_t x = 0; x < particle_per_row; x++) {
        for (uint32_t y = 0; y < particle_per_col; y++) {
            particles[particles_index] = particle_init(x_step * x, y_step * y);
            buffer[get_index(width, height, (int) x_step * (int) x, (int) y_step * (int) y)] = 1;
            particles_index++;
        }
    }
    

    for (uint32_t a = 0; a < steps; a++) {
        for (uint32_t i = 0; i < particles_count; i++) {
            particle_t *particle = particles[i];

            uint32_t x = (uint32_t) particle->x;
            uint32_t y = (uint32_t) particle->y;

            if (x > width || y > height) continue;

            int buffer_index = get_index(width, height, (int) x, (int) y);

            particle->x += (uint32_t) (u_field[buffer_index] * dt);
            particle->y += (uint32_t) (v_field[buffer_index] * dt);

            buffer[buffer_index] = 1;
        }
        if (a % 1000 == 0) {
            printf("%d%% complete\n", a * 100 / steps);
        }
    }

    for (uint32_t i = 0; i < particles_count; i++) {
        free(particles[i]);
    }
    free(particles);
    particles = NULL;

    return buffer;
}

void write_streamlines_to_ppm(ofm_t *ofm, int *streamlines, char *output_file) {
    uint32_t width = ofm->field_width;
    uint32_t height = ofm->field_height;
    uint32_t area = ofm->field_area;

    FILE *fptr = fopen(output_file, "w");

    fprintf(fptr, "P5 %d %d %d\n", width, height, 255);

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int i = get_index(width, height, (int) x, (int) y);
            int streamlines_val = streamlines[i] == 1 ? 255 : 0;

            fputc(streamlines_val, fptr);
        }
    }

    fclose(fptr);
    fptr = NULL;

    return;
}
