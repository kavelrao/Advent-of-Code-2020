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

    for (int i = 0; i < input->length; ++i) {
        char *rule = strtok(input->arr[i], ":");
        char *password = strtok(NULL, "\n");
        char ruleChar = rule[strlen(rule) - 1];

        int min = atoi(strtok(rule, "-"));
        int max = atoi(strtok(NULL, "\n"));
        int count = 0;
        // Start at index 1 because there's a space after the colon
        for (int j = 1; j < strlen(password); ++j) {
            if (password[j] == ruleChar) {
                count++;
            }
        }
        if (count >= min && count <= max) {
            result++;
        }
    }

    printf("%d\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}
