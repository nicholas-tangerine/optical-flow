#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "tiffio.h"

/**
 * converts TIFF into 2d array of ints
 *
 * @param tif               TIFF struct
 * 
 * @return 2d int array
 */
int *readTiffToBuffer(TIFF *tif);
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
