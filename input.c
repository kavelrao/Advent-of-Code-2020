#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "input.h"

input_t *InputRead(char *filename) {
    FILE *fp;
    int i;
    input_t *result;

    // Open file in read mode. On failure return NULL
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File \"%s\" does not exist\n", filename);
        return NULL;
    }

    // Allocate input_t *result. On failure, close file and return NULL.
    result = malloc(sizeof(input_t));
    if (result == NULL) {
        fclose(fp);
        return NULL;
    }

    result->length = InputSize(filename);

    // Allocate result->arr. On failure, free result, close file, and return NULL.
    result->arr = malloc(result->length * sizeof(line_t));
    if (result->arr == NULL) {
        free(result);
        fclose(fp);
        return NULL;
    }

    // Read file line by line, writing the buffer to result->arr.
    size_t maxLine = InputMaxLine(filename);
    for (i = 0; i < result->length; ++i) {
        // Allocate result->arr[i]. On failure, free result, close file, and return NULL.
        result->arr[i] = malloc(maxLine + 1);
        if (result->arr[i] == NULL) {
            InputFree(result);
            fclose(fp);
            return NULL;
        }
        fgets(result->arr[i], maxLine + 1, fp);
    }

    fclose(fp);
    return result;
}

size_t InputSize(char *filename) {
    FILE *fp;
    size_t result;
    char ch;

    // Open the file in read mode. On failure, return 0.
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File \"%s\" does not exist\n", filename);
        return 0;
    }

    result = 0;
    // Read file by character, searching for '\n'.
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            result++;
        }
    }

    fclose(fp);
    return result;
}

size_t InputMaxLine(char *filename) {
    FILE *fp;
    size_t max;
    size_t current;
    char ch;

    // Open the file in read mode. On failure, return 0.
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File \"%s\" does not exist\n", filename);
        return 0;
    }

    max = 0;
    current = 0;
    // Read file by character, searching for '\n'.
    while ((ch = fgetc(fp)) != EOF) {
        current++;
        if (ch == '\n') {
            if (current > max)
                max = current;
            current = 0;
        }
    }

    fclose(fp);
    return max;
}

void InputFree(input_t *input) {
    for (int i = 0; i < input->length; ++i) {
        free(input->arr[i]);
    }
    free(input->arr);
    free(input);
}
