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

#define DARKNESS_THRESHOLD 0.1f

#define DOWNSCALE_FACTOR 4
#define GAUSSIAN_SMOOTH_SIGMA 2
#define GAUSSIAN_SMOOTH_RADIUS (3 * GAUSSIAN_SMOOTH_SIGMA)

#define H_S_ITERATIONS 91
#define H_S_ALPHA 10.0

#define STREAMLINE_ITERATIONS (2000 / DOWNSCALE_FACTOR)
#define STREAMLINE_PARTICLES_PER_ROW (3600 / DOWNSCALE_FACTOR)
#define STREAMLINE_PARTICLES_PER_COL (STREAMLINE_PARTICLES_PER_ROW / 2)
#define STREAMLINE_ITERATIONS_DT 0.5

int main(int argc, char **argv) {
    if (argc < 4) {
        LOG_DEBUG("DEBUG: not enough params\n");
        return 1;
    }

    image_t *img1 = image_init(argv[1], "r");
    image_t *img2 = image_init(argv[2], "r");

    if (!image_same_dimensions(img1 , img2)) {
        LOG_DEBUG("DEBUG: before and after images do not have the same dimensions\n");
        return 1;
    }

    /**
     * PREPROCESS
     */
    PreprocessorConfig config = {
        .downscale = true,
        .match = true,
        .smooth = true,
        .normalize = true,
        .fit = true,
        .write_ppm = false,

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

    LOG_DEBUG("DEBUG: NORMALIZING VELOCITY FIELD\n");
    velocity_field_normalize(ofm);

    LOG_DEBUG("DEBUG: GETTING STREAMLINES\n");
    int *streamlines = draw_streamlines_to_buffer(ofm, STREAMLINE_PARTICLES_PER_ROW, STREAMLINE_PARTICLES_PER_COL, STREAMLINE_ITERATIONS, STREAMLINE_ITERATIONS_DT);
    write_streamlines_to_ppm(ofm, streamlines, "streamlines.ppm");

    LOG_DEBUG("DEBUG: OVERLAYING STREAMLINES\n");
    overlay_streamlines_to_intensity_buffer(img1, streamlines);
    overlay_streamlines_to_intensity_buffer(img2, streamlines);

    LOG_DEBUG("DEBUG: WRITING OVERLAID STREAMLINES\n");
    write_intensity_buffer_to_ppm(img1, "output1-streamlines.ppm");
    write_intensity_buffer_to_ppm(img2, "output2-streamlines.ppm");

    /**
     * FREE MEMORY
     */
    free(streamlines);

    ofm_free(&ofm);

    image_free(&img1);
    image_free(&img2);

    return 0;
}
