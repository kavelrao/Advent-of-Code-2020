#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../input.h"
#include "../strings.h"
#include "../hashmap.h"
#include "../linkedlist.h"


static int countBags(hashmap_t *map, char *bag);
static int traceBags(hashmap_t *map, linkedlist_t *bags);



// light red bags contain 1 bright white bag, 2 muted yellow bags.
// faded blue bags contain no other bags.
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

        linkedlist_t *inners = LinkedListCreate();
        if (strcmp(split->arr[4], "no") != 0) {
            int j = 5;  // first identifier of inner bags
            while (j < split->length) {
                int num = atoi(split->arr[j-1]);
                for (int k = 0; k < num; ++k) {
                    inner = calloc(strlen(split->arr[j]) + strlen(split->arr[j+1]) + 1, sizeof(char));
                    strcpy(inner, split->arr[j]);
                    strcat(inner, split->arr[j+1]);

                    LinkedListAdd(inners, inner);
                }   

                j += 4;
            }
        }
        
        HashmapPut(map, outer, inners);
        StrArrFree(split);
    }
    StrArrFree(input);

    printf("bags in shiny gold: %d\n", countBags(map, "shinygold"));


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

static int countBags(hashmap_t *map, char *bag) {
    return traceBags(map, (linkedlist_t *)HashmapGet(map, bag)) - 1;
}

static int traceBags(hashmap_t *map, linkedlist_t *bags) {
    int count = 1;
    for (int i = 0; i < bags->size; ++i) {
        char *bag = (char *)LinkedListGetValue(bags, i);
        count += traceBags(map, (linkedlist_t *)HashmapGet(map, bag));
    }
    return count;
}