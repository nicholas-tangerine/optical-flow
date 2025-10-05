/**
 * writes buffer to output.ppm; assumes buffer is rgba
 *
 * @param width             image width (pixels)
 * @param height            image height (pixels)
 * @param buffer            image data in int array
 * @param outputFile        name of output file (.ppm)
 */
void writeImageToPPM(uint32_t width, uint32_t height, uint32_t *buffer, char *outputFile);
