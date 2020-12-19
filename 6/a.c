#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"


#define LETTERS 26
int main() {
    int result = 0;
    int count = 0;
    char yes[LETTERS + 1];
    int i;
    int j;

    strarr_t *input = InputReadBlankLines("input.txt");

    for (i = 0; i < input->length; ++i) {
        for (j = 0; j < strlen(input->arr[i]); ++j) {
            if (input->arr[i][j] != '\n' && strchr(yes, input->arr[i][j]) == NULL) {
                yes[count] = input->arr[i][j];
                count++;
            }
        }

        result += count;
        count = 0;
        memset(yes, '\0', LETTERS + 1);
    }


    printf("result: %d\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}
