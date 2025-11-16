#define ENABLE_DEBUG

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tiff_helpers.h"
#include "math_helper.h"
#include "ofm_helper.h"

#include "preprocessor.h"
#include "image.h"
#include "ofm.h"

#include "debug_utils.h"

const double MATCH_SIGMA = 10;
const uint32_t MATCH_RADIUS = 3 * (int) MATCH_SIGMA;

const double DARKNESS_THRESHOLD = 0.1f;

const uint32_t DOWNSCALE_FACTOR = 1;
const uint32_t GAUSSIAN_SMOOTH_SIGMA = 2;
const double GAUSSIAN_SMOOTH_RADIUS = (3 * GAUSSIAN_SMOOTH_SIGMA);

const uint32_t H_S_ITERATIONS = 91;
const double H_S_ALPHA = 10.0;

const uint32_t STREAMLINE_ITERATIONS = 2000;
const uint32_t STREAMLINE_PARTICLES_PER_ROW = 100;
const uint32_t STREAMLINE_PARTICLES_PER_COL = STREAMLINE_PARTICLES_PER_ROW * 7 / 10;
const double STREAMLINE_ITERATIONS_DT = 0.5;

int main(int argc, char **argv) {
    if (argc < 4) {
        LOG_DEBUG("DEBUG: not enough params\n");
        return 1;
    }

    image_t *img1 = image_init(argv[1], "r");
    image_t *img2 = image_init(argv[2], "r");

    /**
     * PREPROCESS
     */
    PreprocessorConfig config = {
        .downscale = true,
        .match = false,//true,
        .smooth = true,
        .normalize = true,
        .fit = true,
        .write_ppm = true,

        .match_radius = MATCH_RADIUS,
        .match_sigma = MATCH_SIGMA,
        .darkness_threshold = DARKNESS_THRESHOLD,
        .scale_factor = DOWNSCALE_FACTOR,
        .gaussian_smooth_radius = GAUSSIAN_SMOOTH_RADIUS,
        .gaussian_smooth_sigma = GAUSSIAN_SMOOTH_SIGMA
    };
    preprocess(img1, img2, &config);

    /**
     * APPLY OFM
     */
    ofm_t *ofm = ofm_init(img1, img2, img1->width, img1->height);
    apply_H_S_estimator(ofm, H_S_ITERATIONS, H_S_ALPHA);

    WritePPMConfig ppm_config = {
        .streamlines_only = true,
        .streamlines_overlay = true,
        .preprocessed_output = true,

        .streamline_particles_per_row = STREAMLINE_PARTICLES_PER_ROW,
        .streamline_particles_per_col = STREAMLINE_PARTICLES_PER_COL,
        .streamline_iterations = STREAMLINE_ITERATIONS,
        .streamline_iterations_dt = STREAMLINE_ITERATIONS_DT
    };

    write_ppms(ofm, img1, img2, &ppm_config);

    /**
     * FREE MEMORY
     */
    //free(streamlines);

    ofm_free(&ofm);

    image_free(&img1);
    image_free(&img2);

    return 0;
}
