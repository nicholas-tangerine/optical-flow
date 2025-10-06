#ifndef TIFFIO_H
#define TIFFIO_H

#include "tiffio.h"

/**
 * Writes RGBA image data to buffer. Saves RGBA (0 - 255)
 *
 * @param tif               pointer to TIFF struct
 * @param buffer            
 */
void tiff_read_to_color_buffer(TIFF *tif, uint32_t *buffer, uint32_t height, uint32_t width);

/**
 * Writes RGBA image data to buffer. Saves B/W (0 - 1)
 *
 * @param tif               pointer to TIFF struct
 * @param buffer            
 */
void tiff_read_to_intensity_buffer(TIFF *tif, float *buffer, uint32_t height, uint32_t width);

/**
 * Returns height of TIFF
 *
 * @param tif               pointer to TIFF struct
 *
 * @return height of TIFF
 */
uint32_t tiff_get_height(TIFF *tif);

/**
 * Returns width of TIFF
 *
 * @param tif               pointer to TIFF struct
 *
 * @return width of TIFF
 */
uint32_t tiff_get_width(TIFF *tif);
#endif
