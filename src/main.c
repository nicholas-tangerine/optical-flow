#include <stdlib.h>

#include "tiff_helpers.h"
#include "math_helper.h"
#include "ofm_helper.h"

#include "preprocessor.h"
#include "image.h"
#include "ofm.h"

#include "debug_utils.h"

#define DOWNSCALE_FACTOR 2
#define GAUSSIAN_SMOOTH_SIGMA 2
#define GAUSSIAN_SMOOTH_RADIUS 3 * GAUSSIAN_SMOOTH_SIGMA
#define ITERATIONS 128
#define H_S_ALPHA 20.0f

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        return 1;
    }

    image_t *img1 = image_init(argv[1], "r");
    image_t *img2 = image_init(argv[2], "r");

    if (!image_same_dimensions(img1 , img2)) {
        fprintf(stderr, "DEBUG: before and after images do not have the same dimensions\n");
        return 1;
    }

    intensity_downscale(img1, DOWNSCALE_FACTOR);
    intensity_downscale(img2, DOWNSCALE_FACTOR);

    intensity_match(img1, img2);

    intensity_smooth(img1, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);
    intensity_smooth(img2, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);

    intensity_normalize(img1);
    intensity_normalize(img2);

    write_intensity_buffer_to_ppm(img1, "output1.ppm");
    write_intensity_buffer_to_ppm(img2, "output2.ppm");

    //double *di_dx = intensity_partial_derivative_field(img1, img2, 'x', 20.0f);
    //double *di_dy = intensity_partial_derivative_field(img1, img2, 'y', 20.0f);
    //double *di_dt = intensity_partial_derivative_field(img1, img2, 't', 20.0f);

    ofm_t *ofm = ofm_init(img1, img2, img1->width, img1->height);

    for (int i = 0; i < ITERATIONS; i++) {
        iterate(ofm, H_S_ALPHA);
    }

    velocity_field_normalize(ofm);

    write_velocity_field_to_file(ofm, "velo field downscaled.txt");

    /**
     * FREE MEMORY
     */
    ofm_free(&ofm);

    image_free(&img1);
    image_free(&img2);

    //free(di_dx);
    //free(di_dy);
    //free(di_dt);

    return 0;
}
