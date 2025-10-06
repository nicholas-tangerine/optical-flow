#include <stdlib.h>
#include <string.h>

#include "preprocessor.h"
#include "tiff_helpers.h"
#include "math_helper.h"

void intensity_smooth(image_t *image, uint32_t radius, float sigma) {
    float **buffer = &(image->intensity_buffer);
    uint32_t width = image->width;
    uint32_t height = image->height;

    uint32_t side_len = 2 * radius + 1;

    float *gaussian_weights_2d = calloc(side_len * side_len, sizeof(float));
    gaussian_dist_2d(gaussian_weights_2d, radius, sigma);

    float *temp_buffer = calloc(width * height, sizeof(float));
    memcpy(temp_buffer, *buffer, width * height * sizeof(float));

    for (uint32_t i = radius; i < height - radius; i++) {
        for (uint32_t j = radius; j < width - radius; j++) {
            uint32_t buffer_index = i * width + j;
            float intensity = weighted_avg(*buffer, gaussian_weights_2d, width, height, side_len, radius, j, i);
            temp_buffer[buffer_index] = intensity;
        }
    }

    free(*buffer);
    *buffer = temp_buffer;

    free(gaussian_weights_2d);

    return;
}

void intensity_normalize(image_t *image) {
    float *buffer = image->intensity_buffer;
    uint32_t width = image->width;
    uint32_t height = image->height;
    float max = 0.0f;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t index = y * width + x;
            float buffer_val = buffer[index];
            max = buffer_val > max ? buffer_val : max;
        }
    }

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t index = y * width + x;
            buffer[index] /= max;
        }
    }
}
