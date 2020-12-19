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

        // Indexes are 1-indexed, but the first character is a space so we don't -1
        int first = atoi(strtok(rule, "-"));
        int last = atoi(strtok(NULL, "\n"));

        if ( (password[first] == ruleChar) ^ (password[last] == ruleChar) )
            result++;
    }

    printf("%d\n", result);

    StrArrFree(input);
    return EXIT_SUCCESS;
}
