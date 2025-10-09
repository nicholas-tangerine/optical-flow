#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "math_helper.h"

float weighted_avg(float *buffer, float *weights, uint32_t image_width, uint32_t image_height, uint32_t kernel_width, uint32_t kernel_height, uint32_t x, uint32_t y) {
    float intensity = 0.0f;

    for (uint32_t i = 0; i < kernel_height; i++) {
        for (uint32_t j = 0; j < kernel_width; j++) {
            uint32_t weights_index = i * kernel_width + j;

            int buffer_index_x = (int) x + (int) j;
            int buffer_index_y = (int) y + (int) i;

            int buffer_index = get_index(image_width, image_height, buffer_index_x, buffer_index_y);

            intensity += weights[weights_index] * buffer[buffer_index];
        }
    }

    return intensity;
}

float average_val(float *buffer, uint32_t buffer_len) {
    float total = 0.0f;
    for (uint32_t i = 0; i < buffer_len; i++) {
        total += buffer[i];
    }

    return (float) total / (float) buffer_len;
}

void increment_buffer(float *buffer, uint32_t buffer_len, float val) {
    for (uint32_t i = 0; i < buffer_len; i++) { buffer[i] += val; }
}

void gaussian_dist_1d(float *weights, uint32_t radius, float sigma) {
    uint32_t side_len = 2 * radius + 1;
    float fraction = 1.0f / (sigma * sqrtf(2.0f * (float) M_PI));
    float exponent;

    for (uint32_t i = 0; i < side_len; i++) {
        exponent = expf(-0.5f * powf((((float) i - (float) radius) / (float) sigma), 2.0f));

        weights[i] = fraction * exponent;
    }

    //  SCALE TO SUM TO 1.0
    float total = 0.0f;
    for (uint32_t i = 0; i < side_len; i++) total += weights[i];
    for (uint32_t i = 0; i < side_len; i++) weights[i] /= total;

    return;
}

void gaussian_dist_2d(float *weights, uint32_t radius, float sigma) {
    uint32_t side_len = 2 * radius + 1;

    float *gaussian_weights_1d = calloc(side_len, sizeof(float));
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
float *difference_of_gaussians_2d(float *buffer1, float *buffer2, uint32_t width, uint32_t height, uint32_t radius, float sigma) {
    uint32_t side_len = 2 * radius + 1;

    float *out = calloc(width * height, sizeof(float));
    float *weights = calloc(side_len * side_len, sizeof(float));
    gaussian_dist_2d(weights, side_len, sigma);

    return out;
}
