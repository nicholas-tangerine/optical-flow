#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "preprocessor.h"
#include "tiff_helpers.h"
#include "math_helper.h"

void intensity_smooth(image_t *image, uint32_t radius, double sigma) {
    double **buffer = &(image->intensity_buffer);
    uint32_t width = image->width;
    uint32_t height = image->height;

    uint32_t side_len = 2 * radius + 1;

    double *gaussian_weights_2d = calloc(side_len * side_len, sizeof(double));
    gaussian_dist_2d(gaussian_weights_2d, radius, sigma);

    double *temp_buffer = calloc(width * height, sizeof(double));
    memcpy(temp_buffer, *buffer, width * height * sizeof(double));

    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            uint32_t buffer_index = i * width + j;
            double intensity = weighted_avg(*buffer, gaussian_weights_2d, width, height, side_len, side_len, (int) j, (int) i);
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

    uint32_t new_width = (uint32_t) ceil((double) width / (double) scale_factor);
    uint32_t new_height = (uint32_t) ceil((double) height / (double) scale_factor);

    uint32_t box_width = (uint32_t) ceil((double) width / (double) new_width);
    uint32_t box_height = (uint32_t) ceil((double) height / (double) new_height);

    double *weights = malloc(box_width * box_height * sizeof(double));
    for (size_t i = 0; i < box_width * box_height; i++) {
        weights[i] = 1.0f;
    }

    for (uint32_t y = 0; y < height; y += box_height) {
        for (uint32_t x = 0; x < width; x += box_width) {
            uint32_t new_y = y / box_height;
            uint32_t new_x = x / box_width;
            double box_sum_intensity = weighted_avg(image->intensity_buffer, weights,
                    width, height,
                    box_width, box_height,
                    (int) x, (int) y);
            double box_avg_intensity = box_sum_intensity / (double) (box_width * box_height);
            image->intensity_buffer[new_y * new_width + new_x] = box_avg_intensity;
        }
    }

    image->width = new_width;
    image->height = new_height;

    free(weights);
}

void intensity_normalize(image_t *image) {
    double *buffer = image->intensity_buffer;
    uint32_t width = image->width;
    uint32_t height = image->height;

    double min = 1e10f;
    double max = 0.0f;
    double diff = 0.0f;

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t index = y * width + x;
            double buffer_val = buffer[index];
            max = buffer_val > max ? buffer_val : max;
            min = buffer_val < min ? buffer_val : min;
        }
    }

    diff = max - min;
    if (diff <= 1e-9) return;
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            uint32_t index = y * width + x;
            buffer[index] -= min;
            buffer[index] /= diff;
        }
    }
}

void intensity_match(image_t *img1, image_t *img2) {
    uint32_t buffer_len = img1->width * img1->height;
    uint32_t temp = img2->width * img2->height;

    if (buffer_len != temp) fprintf(stderr, "DEBUG: intensity_match: img1 and "
            "img2 are different sizes\n");

    double avg1 = average_val(img1->intensity_buffer, buffer_len);
    double avg2 = average_val(img2->intensity_buffer, buffer_len);

    if (avg1 < avg2) increment_buffer(img1->intensity_buffer, buffer_len, avg2 - avg1);
    else increment_buffer(img2->intensity_buffer, buffer_len, avg2 - avg1);
}

void intensity_fit(image_t *img1, image_t *img2, double threshold) {
    int width = (int) img1->width;
    int height = (int) img1->height;

    double *intensity_buffer1 = img1->intensity_buffer;
    double *intensity_buffer2 = img2->intensity_buffer;

    int top1 = INT_MAX;
    int bot1 = INT_MIN;
    int top2 = INT_MAX;
    int bot2 = INT_MIN;

    for (int i = 0 ; i < height; i++) { if (row_is_black(img1, i, threshold)) continue; top1 = i; break; }
    for (int i = 0 ; i < height; i++) { if (row_is_black(img2, i, threshold)) continue; top2 = i; break; }
    for (int i = height-2; i >= 0; i--) { if (row_is_black(img1, i, threshold)) continue; bot1 = i; break; }
    for (int i = height-2; i >= 0; i--) { if (row_is_black(img2, i, threshold)) continue; bot2 = i; break; }

    int top = top1 > top2 ? top1 : top2;
    top = top == INT_MAX ? 0 : top;

    int bot = bot1 < bot2 ? bot1 : bot2;
    bot = bot == INT_MIN ? height-1 : bot;

    int new_height = bot - top + 1;

    double *new_intensity_buffer1 = calloc((size_t) (new_height * width), sizeof(double));
    double *new_intensity_buffer2 = calloc((size_t) (new_height * width), sizeof(double));

    for (int y = top; y < bot; y++) {
        for (int x = 0; x < width; x++) {
            int new_index = (y - top) * width + x;
            int old_index = y * width + x;

            new_intensity_buffer1[new_index] = intensity_buffer1[old_index];
            new_intensity_buffer2[new_index] = intensity_buffer2[old_index];
        }
    }

    free(intensity_buffer1);
    free(intensity_buffer2);

    img1->intensity_buffer = new_intensity_buffer1;
    img2->intensity_buffer = new_intensity_buffer2;

    img1->height = (uint32_t) new_height;
    img2->height = (uint32_t) new_height;

    return;
}

