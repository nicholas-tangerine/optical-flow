#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <stdint.h>

void gaussian_dist_1d(float *weights, uint32_t radius, float sigma);

void gaussian_dist_2d(float *weights, uint32_t radius, float sigma);

#endif
