#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include <stdio.h>

#include "image.h"
#include "ofm.h"

/**
 * Debugging macro
 */
#ifdef ENABLE_DEBUG
#  define LOG_DEBUG(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#  define LOG_DEBUG(fmt, ...) ((void)0)
#endif /* ENABLE_DEBUG */

typedef struct {
    bool streamlines_only;
    bool streamlines_overlay;
    bool preprocessed_output;

    uint32_t streamline_particles_per_row;
    uint32_t streamline_particles_per_col;
    uint32_t streamline_iterations;
    double streamline_iterations_dt;
} WritePPMConfig;

/**
 * Writes color buffer to output_file (default: output.ppm); assumes buffer is
 * rgba
 *
 * @param width             image width (pixels)
 * @param height            image height (pixels)
 * @param buffer            image data in uint32_t array
 * @param output_file       name of output file (.ppm)
 */
void write_color_buffer_to_ppm(image_t *image, char *output_file);

/**
 * Writes intensity buffer to output_file (default: output.ppm); assumes buffer
 * is doubles
 *
 * @param image             pointer to image containing intensity buffer
 * @param output_file       name of output file (.ppm)
 */
void write_intensity_buffer_to_ppm(image_t *image, char *output_file);

/**
 * Writes velocity field to output_file. Formatted as:
 *
 * OUTPUT_FILE
 * ************************************************
 * <width> <height>
 * v_x(0,0) f_y(0,0)
 * v_x(0,1) f_y(0,1)
 * ...
 * v_x(height-1, width-1) v_y(height-1, width-1) 
 * ************************************************
 *
 * @param ofm               pointer to ofm struct with filled u_field and
 * v_field
 * @param output_file       defaults to velo_field.txt when output_file == ""
 */
void write_velocity_field_to_file(ofm_t *ofm, char *output_file);

/**
 * Iteratively draws streamlines by simulating particles travelling through
 * velocity field
 *
 * @param ofm               pointer to ofm struct with u and v field
 * @param particle_per_row  number of simulated particles per row
 * @param particle_per_col  number of simulated particles per col
 * @param steps             number of time steps into future
 * @param dt                change in time between steps
 *
 * @return                  int matrix with value 0 for background and 1 for
 * streamline
 */
int *draw_streamlines_to_buffer(ofm_t *ofm, uint32_t particle_per_row, uint32_t
        particle_per_col, uint32_t steps, double dt);

/**
 * Draws streamlines to ppm file
 *
 * @param ofm               pointer to ofm struct with field width and height
 * values
 * @param streamlines       int matrix with value 1 wherever theres a
 * streamline
 * @param output_file       name of output ppm file$a
 */
void write_streamlines_to_ppm(ofm_t *ofm, int *streamlines, char *output_file);

/**
 * Overlays the streamlines on top of intensity buffer for visualization
 *
 * @param image             pointer to image struct with intensity buffer and
 * dimensions
 * @param streamlines       int matrix with value 1 wherever there is a
 * streamline
 */
void overlay_streamlines_to_intensity_buffer(image_t *image, int *streamlines);

/**
 * Writes various PPM files used to debug streamlines, intensity buffers, etc
 * based on WritePPMConfig
 *
 * @param ofm               ofm struct with velocity field data to generate
 * streamlines
 * @param img1              before image
 * @param img2              after image
 * @param config            WritePPMConfig used to indicate which PPMs to
 * generate
 */
void write_ppms(ofm_t *ofm, image_t *img1, image_t *img2, WritePPMConfig
        *config);
#endif
