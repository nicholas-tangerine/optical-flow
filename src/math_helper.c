#include <stdlib.h>
#include <math.h>

#include "math_helper.h"

void gaussian_dist_1d(float *weights, uint32_t radius, float sigma) {
    uint32_t side_len = 2 * radius + 1;
    float fraction = pow((sigma * sqrtf(2.0f * M_PI)), -1);
    float exponent;

    for (uint32_t i = 0; i < side_len; i++) {
        exponent = expf(-0.5f * pow(((i - radius) / sigma), 2));

        weights[i] = fraction * exponent;
    }

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
