#ifndef FILENAME_UTILS_H
#define FILENAME_UTILS_H

/**
 * returns output file name
 * must be freed by user
 *
 * @param file_name          name of file of form <file_name>.<extension>
 *
 * @return <file_name>_processed.<extension>
 */
char *get_output_name(char *input_name);

#endif
