#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"
#include "../linkedlist.h"

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

    int line = 0;
    int acc;
    i = 0;
    while (i < input->length) {
        if (strcmp(instructions[line]->arr[0], "jmp") == 0) {
            char *prev = instructions[line]->arr[0];
            instructions[line]->arr[0] = "nop";

            for (int j = 0; j < input->length; ++j) {
                done[j] = -1;
            }

            int numDone = 0;
            i = 0;
            acc = 0;
            while (!intInArr(done, i, input->length) && i < input->length) {
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
            instructions[line]->arr[0] = prev;
        }

        else if (strcmp(instructions[line]->arr[0], "nop") == 0) {
            char *prev = instructions[line]->arr[0];
            instructions[line]->arr[0] = "jmp";

            for (int j = 0; j < input->length; ++j) {
                done[j] = -1;
            }

            int numDone = 0;
            i = 0;
            acc = 0;
            while (!intInArr(done, i, input->length) && i < input->length) {
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
            instructions[line]->arr[0] = prev;
        }
        line++;
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