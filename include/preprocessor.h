#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "image.h"
#include "tiffio.h"

typedef struct {
    bool downscale;
    bool match;
    bool smooth;
    bool normalize;
    bool fit;
    bool write_ppm;

    uint32_t match_radius;
    double match_sigma;
    double darkness_threshold;
    uint32_t scale_factor;
    uint32_t gaussian_smooth_radius;
    uint32_t gaussian_smooth_sigma;
} PreprocessorConfig;

/**
 * Smooths intensity buffer using gaussian blur.
 *
 * @param buffer
 * @param width
 * @param height
 * @param radius            radius for the weighted averaging
 * @param sigma             standard deviation of the gauss distribution
 */
void intensity_smooth(image_t *image, uint32_t radius, double sigma);

/**
 * Scales the provided image down by the specified factor.
 *
 * The image will be scaled in-place. The intensity buffer structure of the
 * provided image will not be realloc'ed, but the width and height will be set
 * to the scaled versions.
 *
 * @param image         The image to scale down.
 * @param scale_factor  The factor by which to scale the image.
 */
void intensity_downscale(image_t *image, uint32_t scale_factor);

/**
 * Normalizes image intensity, pixels range from 0 to 1
 *
 * @param buffer            intensity map
 * @param height            img height
 * @param width             img width
 */
void intensity_normalize(image_t *image);

/**
 * Takes two images and brightens the dimmer one such taht their average
 * intensities are equal
 *
 * @param img1
 * @param img2
 */
void intensity_match(image_t *img1, image_t *img2, uint32_t radius, double sigma);

/**
 * Cuts out the black bars at the tops and bottoms of images. Keeps both images
 * sized and centered the same.
 *
 * @param img1              before image
 * @param img2              after image
 * @param threshold         how dark a pixel must be to be black
 */
void intensity_fit(image_t *img1, image_t *img2, double threshold);

/**
 * Preprocessing on both img1 and img2. preprocessing steps are performed based
 * on the flags enabled in config
 *
 * @param img1              before image
 * @param img2              after image
 * @param config            PreprocessorConfig used to indicate what
 *                          preprocessing steps should be taken
 */
void preprocess(image_t *img1, image_t *img2, PreprocessorConfig *config);
#endif
