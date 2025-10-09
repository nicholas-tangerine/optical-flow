#include <stdlib.h>

#include "tiff_helpers.h"
#include "preprocessor.h"
#include "image.h"

#include "debug_utils.h"

#define GAUSSIAN_SMOOTH_SIGMA 2
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

    intensity_downscale(img_before, 6);
    intensity_downscale(img_after, 6);

    intensity_match(img_before, img_after);
    
    intensity_smooth(img_before, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);
    intensity_smooth(img_after, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);

    intensity_normalize(img_before);
    intensity_normalize(img_after);

    write_intensity_buffer_to_ppm(img_before, "output1.ppm");
    write_intensity_buffer_to_ppm(img_after, "output2.ppm");

    float *di_dt = intensity_partial_derivative_field(img_before, img_after, 'x', 20.0f);

    for (uint32_t i = 0; i < img_before->height; i++) {
        for (uint32_t j = 0; j < img_before->width; j++) {
            int index = get_index(img_before->width, img_before->height, j, i);
            //printf("%.2f ", di_dt[index]);
        }
        printf("\n");
    }

    /**
     * FREE MEMORY
     */
    image_free(&img_before);
    image_free(&img_after);

    //free(di_dt);

    return 0;
}
