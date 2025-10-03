#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "tiffio.h"

typedef struct {
    TIFF *imgFileIn;
    TIFF *imgFileOut;
} Preprocessor;

/**
 * creates a Preprocessor struct
 *
 * @param imgFile           name of .tif file to preprocess
 *
 * @return Preprocessor*    pointer to Preprocessor struct
 */
Preprocessor *createPreprocessor(char *fileName);

/**
 * frees Preprocessor struct from heap
 *
 * @param preprocessor      pointer to addr of Preprocessor struct
 */
void deletePrepreprocessor(Preprocessor **preprocessor);

/**
 * gets image dimensions in the form [height, width]
 *
 * @param preprocessor      preprocessor struct holding TIFF img
 * @param imgDimensions     pointer to int array to hold dimensions
 */
void getImgDimensions(Preprocessor *preprocessor, int *imgDimensions);

/**
 * applies gaussian blur to image
 *
 * @param sigma             standard deviation
 */
void applyGaussianBlur(double sigma);

/**
 * normalizes image intensity, pixels range from 0 to 1
 */
void normalize();

/**
 * returns output file name
 * must be freed by user
 *
 * @param fileName          name of file
 *
 * @return <fileName>_processed.<extension>
 */
char *getOutputName(char *fileName);

#endif
