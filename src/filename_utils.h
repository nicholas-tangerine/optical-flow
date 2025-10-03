#ifndef FILENAME_UTILS_H
#define FILENAME_UTILS_H

/**
 * returns output file name
 * must be freed by user
 *
 * @param fileName          name of file
 *
 * @return <fileName>_processed.<extension>
 */
char *getOutputName(char *inputName);

#endif
