#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "tiff_helpers.h"

image_t *image_init(char *file_name, char *mode) {
    //  Allocate img
    image_t *img = calloc(1, sizeof(image_t));

    //  Initialize fields
    img->tif = TIFFOpen(file_name, mode);
    img->height = tiff_get_height(img->tif);
    img->width = tiff_get_width(img->tif);
    img->read = strcmp(mode, "r") == 0 ? true : false;

    img->buffer = (uint32_t *) calloc(img->height * img->width, sizeof(uint32_t));
    tiff_read_to_buffer(img->tif, img->buffer, img->height, img->width);

    return img;
}

void image_free(image_t **img) {
    if (!(*img)->read) {
        fprintf(stderr, "DEBUG: freeing a write file. use image_flush instead\n");
    }
    TIFFClose((*img)->tif);

    free((*img)->buffer);
    (*img)->buffer = NULL;

    free(*img);
    *img = NULL;

    return;
}

bool image_same_dimensions(image_t *img1, image_t *img2) {
    uint32_t height1, width1, height2, width2;
    height1 = img1->height;
    width1 = img1->width;
    height2 = img2->height;
    width2 = img2->width;

    return (height1 == height2 && width1 == width2);
}
