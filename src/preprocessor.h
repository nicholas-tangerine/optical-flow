#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "tiffio.h"

/**
 * Applies Gaussian blur to image
 *
 * @param sigma             standard deviation
 */
void applyGaussianBlur(TIFF *tif, double sigma);

/**
 * Normalizes image intensity, pixels range from 0 to 1
 */
void normalize(TIFF *tif);

#endif
