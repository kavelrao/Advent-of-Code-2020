#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"

#define N 25

bool sumBefore(int num, int index, int count, int *arr);

int main() {
    strarr_t *input = InputRead("input.txt");
    int *nums = malloc(input->length * sizeof(int));
    for (int i = 0; i < input->length; ++i) {
        nums[i] = atoi(input->arr[i]);
    }

    for (int i = N; i < input->length; ++i) {
        if (!sumBefore(nums[i], i, N, nums)) {
            printf("num: %d\n", nums[i]);
        }
    }

    free(nums);
    StrArrFree(input);
    return 0;
}

bool sumBefore(int num, int index, int count, int *arr) {
    for (int i = index - count; i < index; ++i) {
        for (int j = index - count; j < index; ++j) {
            if (i != j && arr[i] + arr[j] == num) {
                return true;
            }
        }
    }
    return false;
}