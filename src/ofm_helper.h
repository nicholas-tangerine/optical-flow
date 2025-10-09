#ifndef OFM_HELPER_H
#define OFM_HELPER_H

#include "image.h"

/**
 * Calculates the partial derivative field in direction `dir`. Assumes that the
 * two images are centered equally.
 *
 * @param img1              before image
 * @param img2              after image
 * @param dir               'x' for d/dx, 'y' for d/dy, 't' for d/dt
 * @param dt                time between images
 *
 * @return d/d[dir]         returns grid with derivative calculated at each
 *                          pixel in intensity buffer **ALLOCATED IN FUNCTION
 *                          BUT MUST BE FREED BY USER**
 */
float *intensity_partial_derivative_field(image_t *img1, image_t *img2, char dir, float dt);

/**
 * Calculates the partial derivative at a point in the x direction. Assumes
 * that the two images are centered equally.
 *
 * @param img1              before image
 * @param img2              after image
 * @param x                 x coordinate to evaluate derivative
 * @param y                 y coordinate to evaluate derivative
 *
 * @return the partial derivative of intensity in the specified direction evaluated at (x,y)
 */
float intensity_d_dx_point(image_t *img1, image_t *img2, int x, int y);

/**
 * Calculates the partial derivative at a point in the y direction. Assumes
 * that the two images are centered equally.
 *
 * @param img1              before image
 * @param img2              after image
 * @param x                 x coordinate to evaluate derivative
 * @param y                 y coordinate to evaluate derivative
 *
 * @return the partial derivative of intensity in the specified direction evaluated at (x,y)
 */
float intensity_d_dy_point(image_t *img1, image_t *img2, int x, int y);

/**
 * Calculates the partial derivative at a point in the t direction. Assumes
 * that the two images are centered equally.
 *
 * @param img1              before image
 * @param img2              after image
 * @param x                 x coordinate to evaluate derivative
 * @param y                 y coordinate to evaluate derivative
 * @param dt                change in time
 *
 * @return the partial derivative of intensity in the specified direction evaluated at (x,y)
 */
float intensity_d_dt_point(image_t *img1, image_t *img2, int x, int y, float dt);
#endif
