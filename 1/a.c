#include <stdio.h>
#include <stdlib.h>
#include "../input.h"
#include "../strings.h"

int main() {
    int target = 2020;
    int result = 0;

    strarr_t *input = InputRead("input.txt");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < input->length; ++i) {
        for (int j = 0; j < input->length; ++j) {
            int n1 = atoi(input->arr[i]);
            int n2 = atoi(input->arr[j]);
            if (n1 + n2 == target)
                result = n1 * n2;
        }
    }

    printf("%d\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}
