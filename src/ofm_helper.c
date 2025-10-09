#include <stdlib.h>
#include <stdio.h>

#include "ofm_helper.h"
#include "math_helper.h"

float *intensity_partial_derivative_field(image_t *img1, image_t *img2, char dir, float dt) {
    if (!image_same_dimensions(img1, img2)) {
        fprintf(stderr, "img1 and img2 do not have the same dimensions");
        exit(1);
    }

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    float *field = calloc(width * height, sizeof(float));

    if (dir == 'x')  {
        for (uint32_t i = 0; i < height - 1; i++) {
            for (uint32_t j = 0; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dx_point(img1, img2, (int) j, (int) i);
            }
        }
    }
    else if (dir == 'y')  {
        for (uint32_t i = 0; i < height - 1; i++) {
            for (uint32_t j = 0; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dy_point(img1, img2, (int) j, (int) i);
            }
        }
    }
    else if (dir == 't')  {
        for (uint32_t i = 0; i < height - 1; i++) {
            for (uint32_t j = 0; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dt_point(img1, img2, (int) j, (int) i, dt);
            }
        }
    }

    return field;
}

float intensity_d_dx_point(image_t *img1, image_t *img2, int x, int y) {
    float *buffer1 = img1->intensity_buffer;
    float *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int ij1k = get_index(width, height, x, y+1);
    int ijk = get_index(width, height, x, y);

    int i1j1k = get_index(width, height, x+1, y+1);
    int i1jk = get_index(width, height, x, y+1);

    int ij1k1 = ij1k;
    int ijk1 = ijk;

    int i1j1k1 = i1j1k;
    int i1jk1 = i1jk;

    float d_intensity = 0.0f;

    d_intensity += buffer1[ij1k] - buffer1[ijk];
    d_intensity += buffer1[i1j1k] - buffer1[i1jk];
    d_intensity += buffer2[ij1k1] - buffer2[ijk1];
    d_intensity += buffer2[i1j1k1] - buffer2[i1jk1];

    d_intensity /= 4.0f;

    return d_intensity ;
}

float intensity_d_dy_point(image_t *img1, image_t *img2, int x, int y) {
    float *buffer1 = img1->intensity_buffer;
    float *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int i1jk = get_index(width, height, x, y+1);
    int ijk = get_index(width, height, x, y);

    int i1j1k = get_index(width, height, x+1, y+1);
    int ij1k = get_index(width, height, x+1, y);

    int i1jk1 = i1jk;
    int ijk1 = ijk;

    int i1j1k1 = i1j1k;
    int ij1k1 = ij1k;

    float d_intensity = 0.0f;

    d_intensity += buffer1[i1jk] - buffer1[ijk];
    d_intensity += buffer1[i1j1k] - buffer1[ij1k];
    d_intensity += buffer2[i1jk1] - buffer2[ijk1];
    d_intensity += buffer2[i1j1k1] - buffer2[ij1k1];

    d_intensity /= 4.0f;

    return d_intensity ;
}

float intensity_d_dt_point(image_t *img1, image_t *img2, int x, int y, float dt) {
    float *buffer1 = img1->intensity_buffer;
    float *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int ijk1 = get_index(width, height, x, y);
    int ijk = ijk1;

    int i1jk1 = get_index(width, height, x, y+1);
    int i1jk = i1jk1;

    int ij1k1 = get_index(width, height, x+1, y);
    int ij1k = ij1k1;

    int i1j1k1 = get_index(width, height, x+1, y+1);
    int i1j1k = i1j1k1;

    float d_intensity = 0.0f;

    d_intensity += buffer2[ijk1] - buffer1[ijk];
    d_intensity += buffer2[i1jk1] - buffer1[i1jk];
    d_intensity += buffer2[ij1k1] - buffer1[ij1k];
    d_intensity += buffer2[i1j1k1] - buffer1[i1j1k];

    d_intensity /= 4.0f;

    d_intensity /= dt;

    return d_intensity ;
}
