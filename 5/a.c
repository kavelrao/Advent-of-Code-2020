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
    int i;
    int j;
    char fb[FB + 1];
    char rl[RL + 1];

    input_t *input = InputRead("input.txt");

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

        if ((row * 8) + col > result)
            result = (row * 8) + col;
    }

    printf("result: %d\n", result);
    InputFree(input);
    return EXIT_SUCCESS;
}
