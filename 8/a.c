#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"

bool intInArr(int *arr, int num, int size);

int main() {
    int i;
    strarr_t *input = InputRead("input.txt");
    strarr_t **instructions = malloc(input->length * sizeof(strarr_t *));

    for (i = 0; i < input->length; ++i) {
        strarr_t *split = StringSplit(input->arr[i], " ");
        instructions[i] = split;
    }

    int *done = malloc(input->length * sizeof(int));
    for (int j = 0; j < input->length; ++j) {
        done[j] = -1;
    }

    int numDone = 0;
    i = 0;
    int acc = 0;
    while (!intInArr(done, i, input->length)) {
        done[numDone] = i;
        numDone++;

        char *command = instructions[i]->arr[0];
        int num = atoi(instructions[i]->arr[1]);

        if (strcmp(command, "acc") == 0) {
            acc += num;
        }

        if (strcmp(command, "jmp") == 0) {
            i += num;
        }
        else {
            i++;
        }
    }

    printf("final acc: %d\n", acc);


    free(done);
    for (int i = 0; i < input->length; ++i) {
        StrArrFree(instructions[i]);
    }
    free(instructions);
    StrArrFree(input);
    return 0;
}

bool intInArr(int *arr, int num, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}