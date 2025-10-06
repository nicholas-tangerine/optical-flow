#include <stdlib.h>
#include <string.h>

#include "preprocessor.h"
#include "tiff_helpers.h"
#include "math_helper.h"

void intensity_smooth(float **buffer, uint32_t width, uint32_t height, int radius, float sigma) {
    int side_len = 2 * radius + 1;

    float gaussian_weights_2d[side_len * side_len];
    gaussian_dist_2d(gaussian_weights_2d, radius, sigma);

    float *temp_buffer = calloc(width * height, sizeof(float));
    memcpy(temp_buffer, *buffer, width * height * sizeof(float));

    for (uint32_t i = side_len; i < height - side_len; i++) {
        for (uint32_t j = side_len; j < width - side_len; j++) {
            int buffer_index = i * width + j;
            float intensity = weighted_avg(*buffer, gaussian_weights_2d, side_len, width, height, j, i);
            temp_buffer[buffer_index] = intensity;
        }
    }

    free(*buffer);
    *buffer = temp_buffer;

    return;
}

float weighted_avg(float *buffer, float *weights, uint32_t side_len, uint32_t width, uint32_t height, int x, int y) {
    float intensity = 0.0f;

    for (uint32_t i = 0; i < side_len; i++) {
        for (uint32_t j = 0; j < side_len; j++) {
            int weights_index = i * side_len + j;

            int buffer_index_x = x - side_len + j;
            int buffer_index_y = y - side_len + i;
            int buffer_index = buffer_index_x * width + buffer_index_y;

            intensity += weights[weights_index] * buffer[buffer_index];
        }
    }

    return intensity;
}

void apply_gaussian_blur(uint32_t *buffer, float sigma) {
    (void) buffer;
    (void) sigma;

    return;
}

void intensity_normalize(float *buffer, uint32_t width, uint32_t height) {
    float max = 0.0f;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int index = y * width + x;
            float buffer_val = buffer[index];
            max = buffer_val > max ? buffer_val : max;
        }
    }

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int index = y * width + x;
            buffer[index] /= max;
        }
    }
}
