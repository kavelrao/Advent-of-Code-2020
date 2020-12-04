#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef INPUT_H_
#define INPUT_H_

// The maximum line size for InputRead
#define BUFFER_LENGTH 128

// Represents a single line of the input file.
typedef char *line_t;

// Represents the input file as an array of lines.
typedef struct line_st {
    line_t *arr;
    size_t length;
} input_t;

// Reads the given file and allocates an array of line_t to store the data.
// It is the client's responsibility to free the input_t * and all subelements
//  by using InputFree.
input_t *InputRead(char *filename);

// Returns the number of lines in the given file
size_t InputSize(char *filename);

// Frees the input and all lines within it
void InputFree(input_t *input);

#endif  // _INPUT_H_
