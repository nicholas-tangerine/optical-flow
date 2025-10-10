#ifndef OFM_H
#define OFM_H

#include <stdint.h>

#include "image.h"

typedef struct {
    double *u_field;       //  x component velocity
    double *v_field;       //  y component velocity

    double *E_x;
    double *E_y;
    double *E_t;

    uint32_t field_width;
    uint32_t field_height;
    uint32_t field_area;

    double *local_velocity_weights;
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
 * Frees all memory relating to ofm struct, including the struct itself
 *
 * @param ofm           pointer to addr of ofm struct
 */
void ofm_free(ofm_t **ofm);

/**
 * Returns the local average x component velocity at a point (x,y)
 *
 * @param ofm           ofm struct
 * @param x             x coordinate to evaluate at
 * @param y             y coordinate to evaluate at
 *
 * @return local average velocity
 */
double local_u(ofm_t *ofm, int x, int y);

/**
 * Returns the local average y component velocity at a point (x,y)
 *
 * @param ofm           ofm struct
 * @param x             x coordinate to evaluate at
 * @param y             y coordinate to evaluate at
 *
 * @return local average velocity
 */
double local_v(ofm_t *ofm, int x, int y);

/**
 * Normalizes a velocity field to range from 0-1
 *
 * @param ofm           ofm struct containing u_field and v_field
 */
void velocity_field_normalize(ofm_t *ofm);

/**
 * Updates ofm struct with new velocity estimates
 *
 * @param ofm           ofm struct
 */
void iterate(ofm_t *ofm, double alpha);
#endif
