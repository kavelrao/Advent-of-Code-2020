/*
 *    Functions used for handling file inputs.
 *    Can be used to obtain array representations of a file or information about a file.
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

// Reads the given file and allocates an array of line_t to store the data line by line.
// It is the client's responsibility to free the strarr_t*.
strarr_t *InputRead(char *filename);

// Reads the given file and allocates an array of line_t to store the data.
// Array elements are divided by blank lines (double newlines) in the file.
// Lines may have newline characters in them where there were single newlines in the file.
// It is the client's responsibility to free the strarr_t*.
strarr_t *InputReadBlankLines(char *filename);

// Returns the number of lines in the given file.
size_t InputSize(char *filename);

// Returns the number of elements in the given file, separated by double newlines.
size_t InputSizeBlankLines(char *filename);

// Returns the maximum number of characters in a line in the given file.
size_t InputMaxLine(char *filename);

#endif  // _INPUT_H_
