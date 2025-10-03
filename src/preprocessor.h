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
 * gets TIFF tags
 *
 * @param tag               the tag index
 *
 * @return pointer to the data corresponding to the tag index
 */
void *getTags(Preprocessor *preprocessor, int tag);

/**
 * prints all the tags in the TIFF file associated with preprocessor struct
 *
 * @param preprocessor      preprocessor struct
 */
void printAllTags(Preprocessor *preprocessor);

/**
 * applies gaussian blur to image
 *
 * @param sigma             standard deviation
 */
void applyGaussianFilter();

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
