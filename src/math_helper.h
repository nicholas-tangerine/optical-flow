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
 * @param kernel_width      the width of the weights matrix
 * @param kernel_height     the height of the weights matrix
 * @param x                 x coordinate of where weights is centered
 * @param y                 y coordinate of where weights is centered
 */
float weighted_avg(float *buffer, float *weights, uint32_t width, uint32_t height, uint32_t kernel_width, uint32_t kernel_height, uint32_t x, uint32_t y);

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

/**
 * Creates a 1d array with terms adding to 1.000
 * Highest point at index `radius`, with sigma being standard deviation
 *
 * @param weights           pointer to array in which gaussian distribution will be stored
 * @param radius            distance from center of array
 * @param sigma             standard deviation
 */
void gaussian_dist_1d(float *weights, uint32_t radius, float sigma);

/**
 * Creates a 2d array with terms adding to 1.000
 * Highest point is at the center of the 2d array, and decays outward according
 * to sigma (standard deviation)
 *
 * @param weights           pointer to array in which gaussian distribution will be stored
 * @param radius            determines the size of the 2d array (N by N matrix with N=2*radius+1
 * @param sigma             standard deviation
 */
void gaussian_dist_2d(float *weights, uint32_t radius, float sigma);

/**
 * TODO: implement
 */
float *difference_of_gaussians_2d(float *buffer1, float *buffer2, uint32_t width, uint32_t height, uint32_t radius, float sigma);
#endif 
