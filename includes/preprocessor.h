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
 * Scales the provided image down by the specified factor.
 *
 * The image will be scaled in-place. The intensity buffer structure of the provided image will
 * not be realloc'ed, but the width and height will be set to the scaled versions.
 *
 * @param image         The image to scale down.
 * @param scale_factor  The factor by which to scale the image.
 */
void intensity_downscale(image_t *image, uint32_t scale_factor);

/**
 * Normalizes image intensity, pixels range from 0 to 1
 *
 * @param buffer            intensity map
 * @param height            img height
 * @param width             img width
 */
void intensity_normalize(image_t *image);

/**
 * Takes two images and brightens the dimmer one such taht their average
 * intensities are equal
 *
 * @param img1
 * @param img2
 */
void intensity_match(image_t *img1, image_t *img2);

#endif
