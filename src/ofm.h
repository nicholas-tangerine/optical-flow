#ifndef OFM_H
#define OFM_H

#include <stdint.h>

#include "image.h"

typedef struct {
    float *u_field;       //  x component velocity
    float *v_field;       //  y component velocity

    float *E_x;
    float *E_y;
    float *E_t;

    uint32_t field_width;
    uint32_t field_height;
    uint32_t field_area;

    float *local_velocity_weights;
    uint32_t weight_width;
    uint32_t weight_height;

} ofm_t;

/**
 * Allocates and initializes a OFM struct
 *
 * @param width         width of the velocity field
 * @param height        height of the velocity field
 *
 * @return ofm          pointer to initialized ofm struct
 */
ofm_t *ofm_init(image_t *img1, image_t *img2, uint32_t width, uint32_t height);

/**
 * Returns the local average x component velocity at a point (x,y)
 *
 * @param ofm           ofm struct
 * @param x             x coordinate to evaluate at
 * @param y             y coordinate to evaluate at
 *
 * @return local average velocity
 */
float local_u(ofm_t *ofm, int x, int y);

/**
 * Returns the local average y component velocity at a point (x,y)
 *
 * @param ofm           ofm struct
 * @param x             x coordinate to evaluate at
 * @param y             y coordinate to evaluate at
 *
 * @return local average velocity
 */
float local_v(ofm_t *ofm, int x, int y);

/**
 * Updates ofm struct with new velocity estimates
 *
 * @param ofm           ofm struct
 */
void iterate(ofm_t *ofm);
#endif
