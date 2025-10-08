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

    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
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

void intensity_downscale(image_t *image, uint32_t scale_factor) {
    uint32_t width = image->width;
    uint32_t height = image->height;

    uint32_t box_width = width / scale_factor;
    uint32_t box_height = height / scale_factor;

    for (uint32_t y = 0; y < height; y += box_height) {
        for (uint32_t x = 0; x < width; x += box_width) {
        }
    }
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

void intensity_match(image_t *img1, image_t *img2) {
    uint32_t buffer_len = img1->width * img1->height;
    uint32_t temp = img2->width * img2->height;

    if (buffer_len != temp) fprintf(stderr, "DEBUG: intensity_match: img1 and \
            img2 are different sizes");

    float avg1 = average_val(img1->intensity_buffer, buffer_len);
    float avg2 = average_val(img2->intensity_buffer, buffer_len);

    if (avg1 < avg2) 
        increment_buffer(img1->intensity_buffer, buffer_len, avg2 - avg1);
    else 
        increment_buffer(img2->intensity_buffer, buffer_len, avg2 - avg1);
}

