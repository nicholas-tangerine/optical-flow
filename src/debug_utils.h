/**
 * writes buffer to output.ppm; assumes buffer is rgba
 *
 * @param buffer            image data in int array
 */

void writeBufferToPPM(uint32_t width, uint32_t height, uint32_t *buffer, char *outputFile);
