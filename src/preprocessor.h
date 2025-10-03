#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

/**
 * applies gaussian blur to image
 *
 * @param sigma             standard deviation
 */
void applyGaussianBlur(double sigma);

/**
 * normalizes image intensity, pixels range from 0 to 1
 */
void normalize();

#endif
