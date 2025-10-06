#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "tiffio.h"

/**
 * Applies Gaussian blur to image buffer
 *
 * @param buffer            RGBA image data in uint32_t buffer
 * @param sigma             standard deviation
 */
void apply_gaussian_blur(uint32_t *buffer, double sigma);

/**
 * Normalizes image intensity, pixels range from 0 to 1
 *
 * @param buffer            intensity map
 * @param height            img height
 * @param width             img width
 */
void intensity_normalize(float *buffer, uint32_t width, uint32_t height);

#endif
