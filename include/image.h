#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

#include "tiffio.h"

typedef struct {
    TIFF *tif;
    uint32_t *color_buffer;
    double *intensity_buffer;
    uint32_t height;
    uint32_t width;
    bool read;

} image_t;

/**
 * Initializes image struct. Returns pointer to image struct which should be
 * freed by calling image_free(image_t **img).
 *
 * @param file_name            name of image file
 *
 * @return image               pointer to image struct
 */
image_t *image_init(char *file_name, char *mode);

/**
 * Frees all memory and sets image pointer to NULL
 * 
 * @param img                   pointer to addr of image_t
 */
void image_free(image_t **img);

/**
 * Allocates and copies existing image_t to new image_t
 *
 * @param img                   preexisting image
 *
 * @return new                  copy of image
 */
image_t *image_copy(image_t *img);

/**
 * Checks whether two image_t structs have the same dimensions
 * 
 * @param img1
 * @param img2
 *
 * @return true if dimensions are equal
 */
bool image_same_dimensions(image_t *img1, image_t *img2);

#endif
