#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"

int main() {
    int result = 0;

    strarr_t *input = InputRead("input.txt");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    int col = 0;
    size_t lineLength = strlen(input->arr[0]) - 2;  // -2 because of padding
    for (int i = 0; i < input->length; ++i) {
        if (col >= lineLength) {
            col = col - lineLength;
        }
        if (input->arr[i][col] == '#') {
            result++;
        }
        col = col + 3;
    }

    printf("%d\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}
