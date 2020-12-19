#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"


long SlopeTrees(strarr_t *input, int right, int down);

int main() {
    long result;

    strarr_t *input = InputRead("input.txt");
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    printf("%c", input->arr[0][31]);

    result = SlopeTrees(input, 1, 1) * SlopeTrees(input, 3, 1) * SlopeTrees(input, 5, 1) * SlopeTrees(input, 7, 1) * SlopeTrees(input, 1, 2);
    printf("%ld\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}

long SlopeTrees(strarr_t *input, int right, int down) {
    size_t lineLength = strlen(input->arr[0]) - 2;  // -2 because of padding
    long result = 0;
    int col = 0;
    for (int i = 0; i < input->length; i += down) {
        if (col >= lineLength) {
            col = col - lineLength;
        }
        if (input->arr[i][col] == '#') {
            result++;
        }
        col += right;
    }
    return result;
}
