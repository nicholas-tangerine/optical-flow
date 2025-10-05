#ifndef TIFFIO_H
#define TIFFIO_H

#include "tiffio.h"

/**
 * Standardize function naming scheme
 */
#define openImg(fileName, mode) TIFFOpen(fileName, mode)

/**
 * Takes pointer to addr of TIFF and frees memory. Sets ptr to NULL
 *
 * @param tif               pointer to addr of TIFF
 */
void freeImg(TIFF **tif);

/**
 * converts TIFF into newly allocated 2d array of ints
 *
 * @param tif               TIFF struct
 * 
 * @return 2d int array
 */
uint32_t *readTiffToBuffer(TIFF *tif);

/**
 * Takes ptr to TIFF and updates imgDimensions to [height, width]
 * 
 * @param tif               pointer to TIFF
 * @param imgDimensions     int array to hold dimensions
 */
void getImgDimensions(TIFF *tif, uint32_t *imgDimensions);

#endif
