#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdint.h>

/**
 * Weighted average of matrix `weights` applied to buffer
 *
 * @param buffer            intensity buffer of with dimensions `height` and `width`
 * @param weights           weights in the kernel with dimensions `kernel_height` and `kernel_width`
 * @param width             width of buffer 
 * @param height            height of buffer
 * @param kernel_width      the width of the weights matrix
 * @param kernel_height     the height of the weights matrix
 * @param x                 x coordinate of top left corner of kernel
 * @param y                 y coordinate of top left corner of kernel
 */
double weighted_avg(double *buffer, double *weights, uint32_t buffer_width, uint32_t buffer_height, uint32_t kernel_width, uint32_t kernel_height, int x, int y);

/**
 * Finds the average value in an array
 *
 * @param buffer            array
 * @param buffer_len        length of array
 *
 * @return avg
 */
double average_val(double *buffer, uint32_t buffer_len);

/**
 * Adds a value `val` to each element in the array
 *
 * @param buffer
 * @param buffer_len
 * @param val
 */
void increment_buffer(double *buffer, uint32_t buffer_len, double val);

/**
 * Creates a 1d array with terms adding to 1.000
 * Highest point at index `radius`, with sigma being standard deviation
 *
 * @param weights           pointer to array in which gaussian distribution will be stored
 * @param radius            distance from center of array
 * @param sigma             standard deviation
 */
void gaussian_dist_1d(double *weights, uint32_t radius, double sigma);

/**
 * Creates a 2d array with terms adding to 1.000
 * Highest point is at the center of the 2d array, and decays outward according
 * to sigma (standard deviation)
 *
 * @param weights           pointer to array in which gaussian distribution will be stored
 * @param radius            determines the size of the 2d array (N by N matrix with N=2*radius+1
 * @param sigma             standard deviation
 */
void gaussian_dist_2d(double *weights, uint32_t radius, double sigma);

/**
 * Gets the index of a 2d array stored in contiguous memory. Mirrors into the 2d array if out of bounds
 *
 * @param width             array width
 * @param height            array height
 * @param x                 x coordinate of wanted index
 * @param y                 y coordinate of wanted index
 *
 * @return index            index in the contiguous memory
 */
int get_index(uint32_t width, uint32_t height, int x, int y);

/**
 * TODO: implement
 */
double *difference_of_gaussians_2d(double *buffer1, double *buffer2, uint32_t width, uint32_t height, uint32_t radius, double sigma);
#endif 
