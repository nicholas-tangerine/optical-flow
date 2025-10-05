/**
 * Writes color buffer to output_file (default: output.ppm); assumes buffer is rgba
 *
 * @param width             image width (pixels)
 * @param height            image height (pixels)
 * @param buffer            image data in int array
 * @param output_file       name of output file (.ppm)
 */
void write_color_buffer_to_ppm(uint32_t *buffer, uint32_t width, uint32_t height, char *output_file);

/**
 * Writes intensity buffer to output_file (default: output.ppm); assumes buffer is floats
 *
 * @param width             image width (pixels)
 * @param height            image height (pixels)
 * @param buffer            image data in int array
 * @param output_file       name of output file (.ppm)
 */
void write_intensity_buffer_to_ppm(float *buffer, uint32_t width, uint32_t height, char *output_file);
