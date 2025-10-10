#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "math_helper.h"

double weighted_avg(double *buffer, double *weights, uint32_t buffer_width, uint32_t buffer_height, uint32_t kernel_width, uint32_t kernel_height, int x, int y) {
    double intensity = 0.0f;

    for (uint32_t i = 0; i < kernel_height; i++) {
        for (uint32_t j = 0; j < kernel_width; j++) {
            uint32_t weights_index = i * kernel_width + j;

            int buffer_index_x = x + (int) j;
            int buffer_index_y = y + (int) i;

            int buffer_index = get_index(buffer_width, buffer_height, buffer_index_x, buffer_index_y);

            intensity += weights[weights_index] * buffer[buffer_index];
        }
    }

    return intensity;
}

double average_val(double *buffer, uint32_t buffer_len) {
    double total = 0.0f;
    for (uint32_t i = 0; i < buffer_len; i++) {
        total += buffer[i];
    }

    return (double) total / (double) buffer_len;
}

void increment_buffer(double *buffer, uint32_t buffer_len, double val) {
    for (uint32_t i = 0; i < buffer_len; i++) { buffer[i] += val; }
}

void gaussian_dist_1d(double *weights, uint32_t radius, double sigma) {
    uint32_t side_len = 2 * radius + 1;
    double fraction = 1.0f / (sigma * sqrt(2.0f * (double) M_PI));
    double exponent;

    for (uint32_t i = 0; i < side_len; i++) {
        exponent = exp(-0.5f * pow((((double) i - (double) radius) / (double) sigma), 2.0f));

        weights[i] = fraction * exponent;
    }

    //  SCALE TO SUM TO 1.0
    double total = 0.0f;
    for (uint32_t i = 0; i < side_len; i++) total += weights[i];
    for (uint32_t i = 0; i < side_len; i++) weights[i] /= total;

    return;
}

void gaussian_dist_2d(double *weights, uint32_t radius, double sigma) {
    uint32_t side_len = 2 * radius + 1;

    double *gaussian_weights_1d = calloc(side_len, sizeof(double));
    gaussian_dist_1d(gaussian_weights_1d, radius, sigma);

    for (uint32_t i = 0; i < side_len; i++) {
        for (uint32_t j = 0; j < side_len; j++) {
            uint32_t index = i * side_len + j;
            weights[index] = gaussian_weights_1d[i] * gaussian_weights_1d[j];
        }
    }

    free(gaussian_weights_1d);

    return;
}

int get_index(uint32_t width, uint32_t height, int x, int y) {
    x = x < 0 ? -x : x;
    x = x >= (int) width ? (int) width - (x - (int) width + 1) : x;

    y = y < 0 ? -y : y;
    y = y >= (int) height ? (int) height - (y - (int) height + 1) : y;

    return y * (int) width + x;
}

//  TODO: actually implement
double *difference_of_gaussians_2d(double *buffer1, double *buffer2, uint32_t width, uint32_t height, uint32_t radius, double sigma) {
    uint32_t side_len = 2 * radius + 1;

    double *out = calloc(width * height, sizeof(double));
    double *weights = calloc(side_len * side_len, sizeof(double));
    gaussian_dist_2d(weights, side_len, sigma);

    return out;
}
