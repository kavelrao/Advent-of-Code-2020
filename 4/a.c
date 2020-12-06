#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../input.h"

int main() {
    int result = 0;
    int count = 0;

    input_t *input = InputRead("input.txt");

    bool byr = false,
         iyr = false,
         eyr = false,
         hgt = false,
         hcl = false,
         ecl = false,
         pid = false;

    for (int i = 0; i < input->length; ++i) {
        if (strstr(input->arr[i], "byr:") != NULL) {
            byr = true;
        }
        if (strstr(input->arr[i], "iyr:") != NULL) {
            iyr = true;
        }
        if (strstr(input->arr[i], "eyr:") != NULL) {
            eyr = true;
        }
        if (strstr(input->arr[i], "hgt:") != NULL) {
            hgt = true;
        }
        if (strstr(input->arr[i], "hcl:") != NULL) {
            hcl = true;
        }
        if (strstr(input->arr[i], "ecl:") != NULL) {
            ecl = true;
        }
        if (strstr(input->arr[i], "pid:") != NULL) {
            pid = true;
        }

        if (input->arr[i][0] == '\n' || i == input->length - 1) {
            count++;
            if (byr && iyr && eyr && hgt && hcl && ecl && pid) {
                result++;
            }
            byr = false;
            iyr = false;
            eyr = false;
            hgt = false;
            hcl = false;
            ecl = false;
            pid = false;
        }
    }


    printf("result: %d\n", result);

    InputFree(input);
    return EXIT_SUCCESS;
}
