#include <stdlib.h>
#include <math.h>

#include "tiff_helpers.h"
#include "math_helper.h"
#include "ofm_helper.h"

#include "preprocessor.h"
#include "image.h"
#include "ofm.h"

#include "debug_utils.h"

#define DARKNESS_THRESHOLD 0.1

#define DOWNSCALE_FACTOR 30
#define GAUSSIAN_SMOOTH_SIGMA 2
#define GAUSSIAN_SMOOTH_RADIUS (3 * GAUSSIAN_SMOOTH_SIGMA)

#define H_S_ITERATIONS 91
#define H_S_ALPHA 10.0

#define STREAMLINE_ITERATIONS 2000
#define STREAMLINE_PARTICLES_PER_ROW 10
#define STREAMLINE_PARTICLES_PER_COL (STREAMLINE_PARTICLES_PER_ROW / 2)
#define STREAMLINE_ITERATIONS_DT 0.5

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

    fprintf(stdout, "DEBUG: DOWNSCALING IMAGES\n");
    intensity_downscale(img1, DOWNSCALE_FACTOR);
    intensity_downscale(img2, DOWNSCALE_FACTOR);

    fprintf(stdout, "DEBUG: MATCHING IMAGE INTENSITIES\n");
    intensity_match(img1, img2);

    fprintf(stdout, "DEBUG: SMOOTHING IMAGE 1\n");
    intensity_smooth(img1, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);
    fprintf(stdout, "DEBUG: SMOOTHING IMAGE 2\n");
    intensity_smooth(img2, GAUSSIAN_SMOOTH_RADIUS, GAUSSIAN_SMOOTH_SIGMA);

    fprintf(stdout, "DEBUG: NORMALIZING IMAGE 1\n");
    intensity_normalize(img1);
    fprintf(stdout, "DEBUG: NORMALIZING IMAGE 2\n");
    intensity_normalize(img2);

    fprintf(stdout, "DEBUG: RESIZING IMAGES\n");
    intensity_fit(img1, img2, DARKNESS_THRESHOLD);

    fprintf(stdout, "DEBUG: PREPROCESSED IMAGES TO PPM\n");
    write_intensity_buffer_to_ppm(img1, "output1.ppm");
    write_intensity_buffer_to_ppm(img2, "output2.ppm");

    //double *di_dx = intensity_partial_derivative_field(img1, img2, 'x', 20.0f);
    //double *di_dy = intensity_partial_derivative_field(img1, img2, 'y', 20.0f);
    //double *di_dt = intensity_partial_derivative_field(img1, img2, 't', 20.0f);

    ofm_t *ofm = ofm_init(img1, img2, img1->width, img1->height);

    fprintf(stdout, "DEBUG: ITERATIVELY SOLVING HORN SCHUNK ESTIMATOR\n");
    for (int i = 0; i < H_S_ITERATIONS; i++) {
        if (i % 30 == 0) fprintf(stdout, "DEBUG: iteration %d\n", i);
        iterate(ofm, H_S_ALPHA);
    }


    fprintf(stdout, "DEBUG: NORMALIZING VELOCITY FIELD\n");
    velocity_field_normalize(ofm);

    /*
    fprintf(stdout, "DEBUG: WRITING VELO FIELD TO TXT FILE\n");
    write_velocity_field_to_file(ofm, "velo field downscaled.txt");*
    */

    fprintf(stdout, "DEBUG: GETTING STREAMLINES\n");
    int *streamlines = draw_streamlines_to_buffer(ofm, STREAMLINE_PARTICLES_PER_ROW, STREAMLINE_PARTICLES_PER_COL, STREAMLINE_ITERATIONS, STREAMLINE_ITERATIONS_DT);
    write_streamlines_to_ppm(ofm, streamlines, "streamlines.ppm");

    fprintf(stdout, "DEBUG: OVERLAYING STREAMLINES\n");
    overlay_streamlines_to_intensity_buffer(img1, streamlines);
    overlay_streamlines_to_intensity_buffer(img2, streamlines);

    fprintf(stdout, "DEBUG: WRITING OVERLAID STREAMLINES\n");
    write_intensity_buffer_to_ppm(img1, "output1-streamlines.ppm");
    write_intensity_buffer_to_ppm(img2, "output2-streamlines.ppm");

    /**
     * FREE MEMORY
     */
    free(streamlines);

    ofm_free(&ofm);

    image_free(&img1);
    image_free(&img2);

    //free(di_dx);
    //free(di_dy);
    //free(di_dt);

    return 0;
}
