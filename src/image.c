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

    img->color_buffer = (uint32_t *) calloc(img->height * img->width, sizeof(uint32_t));
    img->intensity_buffer = (float *) calloc(img->height * img->width, sizeof(float));

    tiff_read_to_color_buffer(img->tif, img->color_buffer, img->height, img->width);
    tiff_read_to_intensity_buffer(img->tif, img->intensity_buffer, img->height, img->width);

    return img;
}

void image_free(image_t **img) {
    if (!(*img)->read) {
        fprintf(stderr, "DEBUG: freeing a write file. use image_flush instead\n");
    }
    TIFFClose((*img)->tif);

    free((*img)->color_buffer);
    (*img)->color_buffer = NULL;

    free((*img)->intensity_buffer);
    (*img)->intensity_buffer = NULL;

    free(*img);
    *img = NULL;

    return;
}

image_t *image_copy(image_t *img) {
    image_t *new = calloc(1, sizeof(image_t));

    new->tif = img->tif;
    new->height = img->height;
    new->width = img->width;
    new->read = img->read;

    int color_size = (int) new->height * (int) new->width * (int) sizeof(uint32_t);
    int intensity_size = (int) new->height * (int) new->width * (int) sizeof(float);

    new->color_buffer = (uint32_t *) calloc(new->height * new->width, sizeof(uint32_t));
    new->intensity_buffer = (float *) calloc(new->height * new->width, sizeof(float));

    memcpy(new->color_buffer, img->color_buffer, (size_t) color_size);
    memcpy(new->intensity_buffer, img->intensity_buffer, (size_t) intensity_size);

    return new;
}

bool image_same_dimensions(image_t *img1, image_t *img2) {
    uint32_t height1, width1, height2, width2;
    height1 = img1->height;
    width1 = img1->width;
    height2 = img2->height;
    width2 = img2->width;

    return (height1 == height2 && width1 == width2);
}
