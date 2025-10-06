#include <stdlib.h>

#include "tiff_helpers.h"
#include "preprocessor.h"
#include "image.h"

#include "debug_utils.h"

#define GAUSSIAN_SMOOTH_SIGMA 3
#define GAUSSIAN_SMOOTH_RADIUS 3*GAUSSIAN_SMOOTH_SIGMA

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        return 1;
    }

    image_t *img_before = image_init(argv[1], "r");
    image_t *img_after = image_init(argv[2], "r");

    if (!image_same_dimensions(img_before, img_after)) {
        fprintf(stderr, "DEBUG: before and after images do not have the same dimensions\n");
        return 1;
    }
    
    intensity_smooth(&(img_before->intensity_buffer), img_before->width, img_before->height, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);

    write_intensity_buffer_to_ppm(img_before->intensity_buffer, img_before->width, img_before->height, "output.ppm");


    /**
     * FREE MEMORY
     */
    image_free(&img_before);
    image_free(&img_after);

    return 0;
}
