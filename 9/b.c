#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"

#define N 18272118

int main() {
    strarr_t *input = InputRead("input.txt");
    int *nums = malloc(input->length * sizeof(int));
    for (int i = 0; i < input->length; ++i) {
        nums[i] = atoi(input->arr[i]);
    }


    for (int i = 0; i < input->length; ++i) {
        int sum = 0;
        int j = i;
        int min = nums[j];
        int max = nums[j];
        while (sum < N && j < input->length) {
            if (nums[j] < min)
                min = nums[j];
            if (nums[j] > max)
                max = nums[j];

            sum += nums[j];
            j++;
        }
        if (sum == N) {
            printf("min + max: %d\n", min + max);
            break;
        }
    }

    free(nums);
    StrArrFree(input);
    return 0;
}