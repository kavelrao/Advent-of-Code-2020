/*
 *    Functions used for manipulating strings.
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INIT_BUFFER 128

// Represents a single string.
typedef char *string_t;

// Represents multiple strings as an array of strings.
typedef struct string_st {
    string_t *arr;
    size_t length;
} strarr_t;

// Returns the given string as an array, split by all characters in the given delims string.
// The resulting strarr_t* must be freed by the user with StrArrFree.
strarr_t *StringSplit(string_t str, string_t separator);

int SubStringCount(string_t str, string_t sub);

// Frees the strarr and all strings within it.
void StrArrFree(strarr_t *input);

#endif  // _STRINGS_H_
