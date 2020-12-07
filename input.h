/*
    Functions used for handling file inputs.
    Can be used to obtain array representations of a file or information about a file.
*/

#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a single line of the input file.
typedef char *line_t;

// Represents the input file as an array of lines.
typedef struct line_st {
    line_t *arr;
    size_t length;
} input_t;

// Reads the given file and allocates an array of line_t to store the data line by line.
// It is the client's responsibility to free the input_t * and all subelements by using InputFree.
input_t *InputRead(char *filename);

// Reads the given file and allocates an array of line_t to store the data.
// Array elements are divided by blank lines (double newlines) in the file.
// Lines may have newline characters in them where there were single newlines in the file.
// It is the client's responsibility to free the input_t * and all subelements by using InputFree.
input_t *InputReadBlankLines(char *filename);

// Returns the number of lines in the given file.
size_t InputSize(char *filename);

// Returns the number of elements in the given file, separated by double newlines.
size_t InputSizeBlankLines(char *filename);

// Returns the maximum number of characters in a line in the given file.
size_t InputMaxLine(char *filename);

// Frees the input and all lines within it
void InputFree(input_t *input);

#endif  // _INPUT_H_
