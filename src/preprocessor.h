#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "image.h"
#include "tiffio.h"

/**
 * Smooths intensity buffer using gaussian blur.
 *
 * @param buffer
 * @param width
 * @param height
 * @param radius            radius for the weighted averaging
 * @param sigma             standard deviation of the gauss distribution
 */
void intensity_smooth(image_t *image, uint32_t radius, float sigma);

/**
 * Applies Gaussian blur to image buffer
 *
 * @param buffer            RGBA image data in uint32_t buffer
 * @param sigma             standard deviation
 */
void apply_gaussian_blur(uint32_t *buffer, float sigma);

/**
 * Normalizes image intensity, pixels range from 0 to 1
 *
 * @param buffer            intensity map
 * @param height            img height
 * @param width             img width
 */
void intensity_normalize(image_t *image);

#endif
