#include <stdio.h>
#include <stdlib.h>
#include "../input.h"

int main() {
    int target = 2020;
    int result = 0;

    input_t *input = InputRead("input.txt");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < input->length; ++i) {
        for (int j = 0; j < input->length; ++j) {
            for (int k = 0; k < input->length; ++k) {
                int n1 = atoi(input->arr[i]);
                int n2 = atoi(input->arr[j]);
                int n3 = atoi(input->arr[k]);
                if (n1 + n2 + n3 == target)
                    result = n1 * n2 * n3;
            }
        }
    }

    printf("%d\n", result);

    InputFree(input);
    return EXIT_SUCCESS;
}
