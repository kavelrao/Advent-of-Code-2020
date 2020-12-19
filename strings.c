#include "strings.h"

strarr_t *StringSplit(string_t str, string_t separator) {
    strarr_t *result;
    char current[strlen(str) +1];
    string_t next;
    int i;

    // Allocate strarr_t *result. On failure return NULL.
    result = malloc(sizeof(strarr_t));
    if (result == NULL) {
        return NULL;
    }

    result->length = SubStringCount(str, separator) + 1;

    // Allocate result->arr. On failure, free result and return NULL.
    result->arr = malloc(result->length * sizeof(string_t));
    if (result->arr == NULL) {
        free(result);
        return NULL;
    }

    for (i = 0; i < result->length; ++i) {
        strcpy(current, str);
        next = strstr(current, separator);  // next points to the next separator in the string

        // Allocate result->arr[i]. On failure, free result and return NULL.
        result->arr[i] = calloc(strlen(current) + 1, sizeof(*(result->arr[i])));
        if (result->arr[i] == NULL) {
            StrArrFree(result);
            return NULL;
        }

        // This means there are no separators left,
        // so result->arr[i] will be a blank string
        if (next == NULL) {
            strcpy(result->arr[i], current);
        }

        else {
            current[next - current] = '\0';
            strcpy(result->arr[i], current);
        }

        // Advance the string pointer to after the separator we just split by
        str += strlen(result->arr[i]) + strlen(separator);
    }

    return result;
}

int SubStringCount(string_t str, string_t sub) {
    char *strptr;
    int count;

    // If the substring is longer than the string, there cannot be any occurences.
    if (strlen(sub) > strlen(str)) {
        return 0;
    }

    count = 0;
    strptr = str;
    while ( (strptr = strstr(strptr, sub)) != NULL) {
        count++;
        strptr += strlen(sub);
    }

    return count;
}

void StrArrFree(strarr_t *strarr) {
    for (int i = 0; i < strarr->length; ++i) {
        if (strarr->arr[i] != NULL) {
            free(strarr->arr[i]);
        }
    }

    free(strarr->arr);
    free(strarr);
}
