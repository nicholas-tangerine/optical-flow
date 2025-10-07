#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdint.h>

/**
 * Weighted average of matrix `weights` applied to buffer
 *
 * @param buffer
 * @param weights
 * @param width             width of buffer 
 * @param height            height of buffer
 * @param side_len
 * @param radius
 * @param x                 x coordinate of where weights is centered
 * @param y                 y coordinate of where weights is centered
 */
float weighted_avg(float *buffer, float *weights, uint32_t width, uint32_t height, uint32_t side_len, uint32_t radius, uint32_t x, uint32_t y);

/**
 * Finds the average value in an array
 *
 * @param buffer            array
 * @param buffer_len        length of array
 *
 * @return avg
 */
float average_val(float *buffer, uint32_t buffer_len);

/**
 * Adds a value `val` to each element in the array
 *
 * @param buffer
 * @param buffer_len
 * @param val
 */
void increment_buffer(float *buffer, uint32_t buffer_len, float val);

void gaussian_dist_1d(float *weights, uint32_t radius, float sigma);

void gaussian_dist_2d(float *weights, uint32_t radius, float sigma);

float *difference_of_gaussians_2d(float *buffer1, float *buffer2, uint32_t width, uint32_t height, uint32_t radius, float sigma);

#endif
