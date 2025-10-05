#include <stdbool.h>

#include "tiffio.h"

typedef struct {
    TIFF *tif;
    uint32_t *buffer;
    uint32_t height;
    uint32_t width;
    bool read;

} Image;

/**
 * Initializes image struct. Returns pointer to image struct which must be
 * freed by calling freeImage(Image **img).
 *
 * @param fileName              name of image file
 *
 * @return image                pointer to image struct
 */
Image *initImage(char *fileName, char *mode);

/**
 * Frees all memory and sets image pointer to NULL
 * 
 * @param img                   pointer to addr of Image
 */
void freeImage(Image **img);

/**
 * Checks whether two Image structs have the same dimensions
 * 
 * @param img1
 * @param img2
 *
 * @return true if dimensions are equal
 */
bool sameDimensions(Image *img1, Image *img2);
