#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

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
void intensity_smooth(float **buffer, uint32_t width, uint32_t height, int radius, float sigma);

/**
 * Weighted average of matrix `weights` applied to buffer
 *
 * @param buffer
 * @param weights
 * @param side_len
 * @param width             width of buffer 
 * @param height            height of buffer
 * @param x                 x coordinate of where weights is centered
 * @param y                 y coordinate of where weights is centered
 */
float weighted_avg(float *buffer, float *weights, uint32_t side_len, uint32_t width, uint32_t height, int x, int y);

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
void intensity_normalize(float *buffer, uint32_t width, uint32_t height);

#endif
