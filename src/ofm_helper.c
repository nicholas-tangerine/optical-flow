#include <stdlib.h>
#include <stdio.h>

#include "ofm_helper.h"
#include "math_helper.h"

double *intensity_partial_derivative_field(image_t *img1, image_t *img2, char dir, double dt) {
    if (!image_same_dimensions(img1, img2)) {
        fprintf(stderr, "img1 and img2 do not have the same dimensions");
        exit(1);
    }

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    double *field = calloc(width * height, sizeof(double));

    if (dir == 'x')  {
        for (uint32_t i = 1; i < height - 1; i++) {
            for (uint32_t j = 1; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dx_point(img1, img2, (int) j, (int) i);
            }
        }
    }
    else if (dir == 'y')  {
        for (uint32_t i = 1; i < height - 1; i++) {
            for (uint32_t j = 1; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dy_point(img1, img2, (int) j, (int) i);
            }
        }
    }
    else if (dir == 't')  {
        for (uint32_t i = 1; i < height - 1; i++) {
            for (uint32_t j = 1; j < width - 1; j++) {
                int field_index = get_index(width, height, (int) j, (int) i);
                field[field_index] = intensity_d_dt_point(img1, img2, (int) j, (int) i, dt);
            }
        }
    }

    return field;
}

double intensity_d_dx_point(image_t *img1, image_t *img2, int x, int y) {
    double *buffer1 = img1->intensity_buffer;
    double *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int idx_xy    = get_index(width, height, x,     y);
    int idx_x1y   = get_index(width, height, x + 1, y);
    int idx_xy1   = get_index(width, height, x,     y + 1);
    int idx_x1y1  = get_index(width, height, x + 1, y + 1);

    double d_intensity = 0.0;

    d_intensity += buffer1[idx_x1y]  - buffer1[idx_xy];
    d_intensity += buffer1[idx_x1y1] - buffer1[idx_xy1];
    d_intensity += buffer2[idx_x1y]  - buffer2[idx_xy];
    d_intensity += buffer2[idx_x1y1] - buffer2[idx_xy1];

    d_intensity /= 4.0;

    return d_intensity;
}

double intensity_d_dy_point(image_t *img1, image_t *img2, int x, int y) {
    double *buffer1 = img1->intensity_buffer;
    double *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int idx_xy    = get_index(width, height, x,     y);
    int idx_x1y   = get_index(width, height, x + 1, y);
    int idx_xy1   = get_index(width, height, x,     y + 1);
    int idx_x1y1  = get_index(width, height, x + 1, y + 1);

    double d_intensity = 0.0;

    d_intensity += buffer1[idx_xy1]  - buffer1[idx_xy];
    d_intensity += buffer1[idx_x1y1] - buffer1[idx_x1y];
    d_intensity += buffer2[idx_xy1]  - buffer2[idx_xy];
    d_intensity += buffer2[idx_x1y1] - buffer2[idx_x1y];

    d_intensity /= 4.0;

    return d_intensity;
}

double intensity_d_dt_point(image_t *img1, image_t *img2, int x, int y, double dt) {
    double *buffer1 = img1->intensity_buffer;
    double *buffer2 = img2->intensity_buffer;

    uint32_t width = img1->width;
    uint32_t height = img1->height;

    int idx_xy    = get_index(width, height, x,     y);
    int idx_x1y   = get_index(width, height, x + 1, y);
    int idx_xy1   = get_index(width, height, x,     y + 1);
    int idx_x1y1  = get_index(width, height, x + 1, y + 1);

    double d_intensity = 0.0;

    d_intensity += buffer2[idx_xy]  - buffer1[idx_xy];
    d_intensity += buffer2[idx_x1y] - buffer1[idx_x1y];
    d_intensity += buffer2[idx_xy1] - buffer1[idx_xy1];
    d_intensity += buffer2[idx_x1y1] - buffer1[idx_x1y1];

    d_intensity /= 4.0;
    d_intensity /= dt;

    return d_intensity;
}
