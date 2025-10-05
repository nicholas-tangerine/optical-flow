#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "tiff_helpers.h"

Image *initImage(char *fileName, char *mode) {
    //  Allocate img
    Image *img = calloc(1, sizeof(Image));

    //  Initialize fields
    img->tif = TIFFOpen(fileName, mode);
    img->height = getTIFFHeight(img->tif);
    img->width = getTIFFWidth(img->tif);
    img->read = strcmp(mode, "r") == 0 ? true : false;

    img->buffer = (uint32_t *) calloc(img->height * img->width, sizeof(uint32_t));
    readTIFFToBuffer(img->tif, img->buffer, img->height, img->width);

    return img;
}

void freeImage(Image **img) {
    TIFFClose((*img)->tif);

    free((*img)->buffer);
    (*img)->buffer = NULL;

    free(*img);
    *img = NULL;

    return;
}

bool sameDimensions(Image *img1, Image *img2) {
    uint32_t height1, width1, height2, width2;
    height1 = img1->height;
    width1 = img1->width;
    height2 = img2->height;
    width2 = img2->width;

    return (height1 == height2 && width1 == width2);
}
