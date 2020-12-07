#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../input.h"


#define LETTERS 26
int main() {
    int result = 0;
    int count = 0;
    int members = 1;
    char yes[LETTERS + 1];
    int yesCount[LETTERS];
    int i;
    int j;

    input_t *input = InputReadBlankLines("input.txt");

    for (i = 0; i < input->length; ++i) {
        for (j = 0; j < strlen(input->arr[i]); ++j) {
            if (input->arr[i][j] == '\n')
                ++members;
            else if (strchr(yes, input->arr[i][j]) == NULL) {
                yes[count] = input->arr[i][j];
                yesCount[count] = 1;
                ++count;
            }
            else {
                ++yesCount[strchr(yes, input->arr[i][j]) - yes];
            }
        }

        for (j = 0; j < count; ++j) {
            if (yesCount[j] == members) {
                ++result;
            }
            yesCount[j] = 0;
        }
        count = 0;
        members = 1;
        memset(yes, '\0', LETTERS + 1);
    }


    printf("result: %d\n", result);

    InputFree(input);
    return EXIT_SUCCESS;
}
