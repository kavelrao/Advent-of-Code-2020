#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../input.h"


#define FB 7
#define RL 3
int main() {
    int result = 0;
    long row;
    long col;
    long id;
    long *ids;
    int idsLength;
    int i;
    int j;
    char fb[FB + 1];
    char rl[RL + 1];

    input_t *input = InputRead("input.txt");

    ids = calloc(input->length, sizeof(*ids));
    idsLength = 0;
    for (i = 0; i < input->length; ++i) {
        for (j = 0; j < 7; ++j) {
            if (input->arr[i][j] == 'F')
                fb[j] = '0';
            else
                fb[j] = '1';
        }
        for (j = 7; j < 10; ++j) {
            if (input->arr[i][j] == 'L')
                rl[j - 7] = '0';
            else
                rl[j - 7] = '1';
        }

        row = strtol(fb, NULL, 2);
        col = strtol(rl, NULL, 2);

        // Insert the new id into a sorted position in the list of ids.
        id = (row * 8) + col;
        j = 0;
        while (id > ids[j] && j < idsLength) {
            j++;
        }
        if (j < idsLength) {
            for (int n = idsLength; n > j; --n) {
                ids[n] = ids[n - 1];
            }
        }
        ids[j] = id;
        idsLength++;
    }

    for (i = 0; i < idsLength - 2; ++i) {
        if (ids[i + 1] - ids[i] == 2) {
            result = ids[i] + 1;
        }
    }


    printf("result: %d\n", result);
    free(ids);
    InputFree(input);
    return EXIT_SUCCESS;
}
