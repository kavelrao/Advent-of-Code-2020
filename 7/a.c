#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"
#include "../hashmap.h"
#include "../linkedlist.h"


static int countBags(hashmap_t *map);
static bool traceBags(hashmap_t *map, linkedlist_t *bags);


int main() {
    strarr_t *input = InputRead("input.txt");

    hashmap_t *map = HashmapCreate();

    // Go through each line, add bag encapsulation into hashmap
    // with key=outer bag, value=linked list of inner bags.
    char *outer;
    char *inner;
    for (int i = 0; i < input->length; ++i) {
        strarr_t *split = StringSplit(input->arr[i], " ");
        outer = calloc(strlen(split->arr[0]) + strlen(split->arr[1]) + 1, sizeof(char));
        strcpy(outer, split->arr[0]);
        strcat(outer, split->arr[1]);

        int j = 5;  // first identifier of inner bags
        linkedlist_t *inners = LinkedListCreate();
        while (j < split->length) {
            inner = calloc(strlen(split->arr[j]) + strlen(split->arr[j+1]) + 1, sizeof(char));
            strcpy(inner, split->arr[j]);
            strcat(inner, split->arr[j+1]);

            // If no inner bags, leave empty list
            if (strcmp(inner, "otherbags.\n") == 0) {
                free(inner);
            }
            else {
                LinkedListAdd(inners, inner);
            }
            j += 4;
        }
        
        HashmapPut(map, outer, inners);
        StrArrFree(split);
    }
    StrArrFree(input);

    printf("paths to shiny gold: %d\n", countBags(map));


    // Free all remaining allocated blocks.
    linkedlist_t *list = HashmapGetKeys(map);
    for (int i = 0; i < list->size; ++i) {
        char *key = (char *) LinkedListGetValue(list, i);
        linkedlist_t *inners = HashmapGet(map, key);
        for (int j = 0; j < inners->size; ++j) {
            free((char *) LinkedListGetValue(inners, j));
        }
        LinkedListFree(inners);
        free(key);
    }

    LinkedListFree(list);
    HashmapFree(map);
    
    return 0;
}

static int countBags(hashmap_t *map) {
    int count = 0;
    linkedlist_t *keys = HashmapGetKeys(map);
    for (int i = 0; i < keys->size; ++i) {
        if (traceBags(map, (linkedlist_t *)HashmapGet(map, (char *)LinkedListGetValue(keys, i))))
            count++;
    }
    return count;
}

static bool traceBags(hashmap_t *map, linkedlist_t *bags) {
    if (bags->size == 0) {
        return false;
    }
    if (LinkedListContainsString(bags, "shinygold")) {
        return true;
    }

    for (int i = 0; i < bags->size; ++i) {
        linkedlist_t *newBags = HashmapGet(map, (char *)LinkedListGetValue(bags, i));
        if (traceBags(map, newBags)) {
            return true;
        }
    }
    return false;
}