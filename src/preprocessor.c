#include <stdlib.h>

#include "preprocessor.h"
#include "tiff_helpers.h"

void apply_gaussian_blur(uint32_t *tif, double sigma) {
    (void) tif;
    (void) sigma;
    return;
}

void intensity_normalize(float *buffer, uint32_t width, uint32_t height ) {
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
