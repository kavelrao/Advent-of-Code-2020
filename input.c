#include "input.h"

input_t *InputRead(char *filename) {
    FILE *fp;
    int i;
    input_t *result;
    size_t maxLine;

    // Open file in read mode. On failure return NULL.
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

    maxLine = InputMaxLine(filename);
    // Read file line by line, writing the buffer to result->arr.
    for (i = 0; i < result->length; ++i) {
        // Allocate result->arr[i]. On failure, free result, close file, and return NULL.
        result->arr[i] = calloc(maxLine + 1, sizeof(*(result->arr[i])));
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

input_t *InputReadBlankLines(char *filename) {
    FILE *fp;
    int i;
    int j;
    char ch1;
    char ch2;
    input_t *result;
    size_t maxLine;

    // Open file in read mode. On failure return NULL.
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

    result->length = InputSizeBlankLines(filename);

    // Allocate result->arr. On failure, free result, close file, and return NULL.
    result->arr = malloc(result->length * sizeof(line_t));
    if (result->arr == NULL) {
        free(result);
        fclose(fp);
        return NULL;
    }

    // ch1 is to put into result->arr.
    // ch2 is to check for consecutive \n chars.
    ch1 = fgetc(fp);
    ch2 = fgetc(fp);

    i = 0;
    maxLine = InputMaxLine(filename);
    // Parse file by character, moving to the next array element on double newlines.
    while (ch2 != EOF) {
        // Allocate result->arr[i]. On failure, free result, close file, and return NULL.
        result->arr[i] = calloc(maxLine + 1, sizeof(*(result->arr[i])));
        if (result->arr[i] == NULL) {
            InputFree(result);
            fclose(fp);
            return NULL;
        }

        // As long as we don't have double newline or EOF, read file by character, ignoring newlines.
        j = 0;
        while ( !(ch1 == '\n' && ch2 == '\n') && ch2 != EOF) {
            // If result->arr[i] is full, reallocate to double the size.
            // The increase to maxLine is permanent to avoid excessive reallocations.
            if (strlen(result->arr[i]) >= maxLine) {
                maxLine = maxLine * 2 + 1;
                result->arr[i] = realloc(result->arr[i], maxLine);
                if (result->arr[i] == NULL) {
                    InputFree(result);
                    fclose(fp);
                    return NULL;
                }
            }

            // Add ch1 into the line, and advance chars.
            result->arr[i][j] = ch1;
            ++j;
            ch1 = ch2;
            ch2 = fgetc(fp);
        }

        // Add null terminator and advance ch1 and ch2, skipping newlines.
        result->arr[i][j] = '\0';
        ch1 = fgetc(fp);
        ch2 = fgetc(fp);
        ++i;
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

size_t InputSizeBlankLines(char *filename) {
    FILE *fp;
    size_t result;
    char ch1;
    char ch2;

    // Open the file in read mode. On failure, return 0.
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "File \"%s\" does not exist\n", filename);
        return 0;
    }

    result = 0;
    // Read file by character, searching for '\n\n'.
    ch1 = fgetc(fp);
    while ((ch2 = fgetc(fp)) != EOF) {
        if (ch1 == '\n' && ch2 == '\n') {
            result++;
        }
        ch1 = ch2;
    }
    // Add one more for the final group that has no trailing \n\n.
    result++;

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
        if (input->arr[i] != NULL) {
            free(input->arr[i]);
        }
    }

    free(input->arr);
    free(input);
}
