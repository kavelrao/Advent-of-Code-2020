#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../input.h"

int main() {
    int result = 0;
    int count = 0;
    char *filename = "input.txt";

    input_t *input = InputRead(filename);

    bool byr = false,
         iyr = false,
         eyr = false,
         hgt = false,
         hcl = false,
         ecl = false,
         pid = false;

    char *delim = " \n";  // Delimiters that break up passport fields
    size_t maxLine = InputMaxLine(filename);

    // Temp string to copy input lines into for manipulation.
    char *temp = calloc((maxLine + 1), sizeof(char));
    if (temp == NULL) {
        InputFree(input);
        fprintf(stderr, "temp alloc failed.");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < input->length; ++i) {
        // Goes through each line, looking for the keys.
        // On finding a key, checks if its value is valid.
        // Increments result and resets counters on a blank line or last line of file.

        // byr: four digits; min 1920, max 2002
        if (strstr(input->arr[i], "byr:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *byrVal = strtok(strstr(temp, "byr:") + 4, delim);
            if (strlen(byrVal) == 4)
                byr = atoi(byrVal) <= 2002 && atoi(byrVal) >= 1920;
        }
        // iyr: four digits; min 2010, max 2020
        if (strstr(input->arr[i], "iyr:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *iyrVal = strtok(strstr(temp, "iyr:") + 4, delim);
            if (strlen(iyrVal) == 4)
                iyr = atoi(iyrVal) <= 2020 && atoi(iyrVal) >= 2010;
        }
        // eyr: four digits; min 2020, max 2030
        if (strstr(input->arr[i], "eyr:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *eyrVal = strtok(strstr(temp, "eyr:") + 4, delim);
            if (strlen(eyrVal) == 4)
                eyr = atoi(eyrVal) <= 2030 && atoi(eyrVal) >= 2020;
        }
        // hgt: number followed by "cm" or "in"
            // if "cm": min 150, max 193
            // if "in": min 59, max 76
        if (strstr(input->arr[i], "hgt:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *hgtVal = strtok(strstr(temp, "hgt:") + 4, delim);
            char *units = hgtVal + (strlen(hgtVal) - 2);
            if (strcmp(units, "cm") == 0) {
                hgt = atoi(strtok(hgtVal, "c")) >= 150 && atoi(strtok(hgtVal, "c")) <= 193;
            }
            if (strcmp(units, "in") == 0) {
                hgt = atoi(strtok(hgtVal, "i")) >= 59 && atoi(strtok(hgtVal, "i")) <= 76;
            }
        }
        // hcl: # followed by exactly 6 characters 0-9 or a-f
        if (strstr(input->arr[i], "hcl:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *hclVal = strtok(strstr(temp, "hcl:") + 4, delim);
            if (hclVal[0] == '#') {
                hclVal++;
                if ( (strlen(hclVal) == 6) && (strtol(hclVal, NULL, 16) != 0) ) {
                    hcl = true;
                }
            }
        }
        // ecl: must be one of {amb, blu, brn, gry, grn, hzl, oth}
        if (strstr(input->arr[i], "ecl:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *eclVal = strtok(strstr(temp, "ecl:") + 4, delim);
            ecl = (strcmp(eclVal, "amb") == 0) || (strcmp(eclVal, "blu") == 0) ||
                  (strcmp(eclVal, "brn") == 0) || (strcmp(eclVal, "gry") == 0) ||
                  (strcmp(eclVal, "grn") == 0) || (strcmp(eclVal, "hzl") == 0) ||
                  (strcmp(eclVal, "oth") == 0);
        }
        // pid: nine digit number
        if (strstr(input->arr[i], "pid:") != NULL) {
            strcpy(temp, input->arr[i]);
            char *pidVal = strtok(strstr(temp, "pid:") + 4, delim);
            pid = (strlen(pidVal) == 9) && (atoi(pidVal) != 0);
        }

        // On a blank line (end of passport), increment result if all fields are valid and reset all fields.
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
    printf("total count: %d\n", count);

    free(temp);
    InputFree(input);
    return EXIT_SUCCESS;
}
