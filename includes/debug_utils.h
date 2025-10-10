#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#include "image.h"
#include "ofm.h"

/**
 * Writes color buffer to output_file (default: output.ppm); assumes buffer is rgba
 *
 * @param width             image width (pixels)
 * @param height            image height (pixels)
 * @param buffer            image data in uint32_t array
 * @param output_file       name of output file (.ppm)
 */
void write_color_buffer_to_ppm(image_t *image, char *output_file);

/**
 * Writes intensity buffer to output_file (default: output.ppm); assumes buffer is doubles
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
 * @param ofm               pointer to ofm struct with filled u_field and v_field
 * @param output_file       defaults to velo_field.txt when output_file == ""
 */
void write_velocity_field_to_file(ofm_t *ofm, char *output_file);
#endif
