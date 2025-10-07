#include <stdlib.h>

#include "tiffio.h"

#include "tiff_helpers.h"


void tiff_read_to_color_buffer(TIFF *tif, uint32_t *buffer, uint32_t height, uint32_t width) {
    int res = TIFFReadRGBAImageOriented(tif, width, height, buffer,
            ORIENTATION_TOPLEFT, 0);

    if (res != 1) {
        fprintf(stderr, "DEBUG: error reading TIFF into buffer");
        return;
    }
}

void tiff_read_to_intensity_buffer(TIFF *tif, float *buffer, uint32_t height, uint32_t width) {
    uint32_t *temp_buffer = calloc(height * width, sizeof(uint32_t));
    int res = TIFFReadRGBAImageOriented(tif, width, height, temp_buffer,
            ORIENTATION_TOPLEFT, 0);

    if (res != 1) {
        fprintf(stderr, "DEBUG: error reading TIFF into temp buffer\n");
        return;
    }

    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            int index = (int)y * (int)width + (int)x;
            uint32_t temp_buffer_val = temp_buffer[index];

            unsigned int r = TIFFGetR(temp_buffer_val);
            unsigned int g = TIFFGetG(temp_buffer_val);
            unsigned int b = TIFFGetB(temp_buffer_val);
            unsigned int a = TIFFGetA(temp_buffer_val);

            float avg_color = (float) (r + g + b) / 3.0f;
            float alpha_frac = (float) a / 255.0f;
            float intensity = (avg_color * alpha_frac) / 255.0f;

            if (intensity < 0.0f) intensity = 0.0f;
            if (intensity > 1.0f) intensity = 1.0f;

            buffer[index] = intensity;
        }
    }


    free(temp_buffer);
}

uint32_t tiff_get_height(TIFF *tif) {
    uint32_t height;

    int res = TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);

    if (res == 1) return height;

    fprintf(stderr, "DEBUG: couldn't get TIFF height\n");
    return height;
}

uint32_t tiff_get_width(TIFF *tif) {
    uint32_t width;

    int res = TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);

    if (res == 1) return width;

    fprintf(stderr, "DEBUG: couldn't get TIFF width\n");
    return width;
}
