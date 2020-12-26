#include "hashmap.h"


// Hash function to convert key into index.
static unsigned hash(size_t M, char *key);


hashmap_t *HashmapCreate() {
    // Allocate hashmap. On failure, return NULL.
    hashmap_t *map = malloc(sizeof(hashmap_t));
    if (map == NULL) {
        return NULL;
    }

    map->tableSize = INIT_SIZE;
    
    // Allocate table. On failure, free map and return NULL.
    map->table = (linkedlist_t **) malloc(map->tableSize * sizeof(linkedlist_t *));
    if (map->table == NULL) {
        free(map);
        return NULL;
    }

    // Initialize linked lists in each table slot.
    // TODO not sure if pointer assignment works like this
    for (int i = 0; i < map->tableSize; ++i) {
        map->table[i] = LinkedListCreate();
        if (map->table[i] == NULL) {
            HashmapFree(map);
            return NULL;
        }
    }

    return map;
}

void *HashmapGet(hashmap_t *map, char *key) {
    linkedlist_t *list = map->table[hash(map->tableSize, key)];
    for (int i = 0; i < list->size; ++i) {
        
        if (LinkedListGetValue(list, i) == NULL) {
            return NULL;
        }
        
        element_t *element = (element_t *) LinkedListGetValue(list, i);
        if (strcmp(element->key, key) == 0) {
            return element->data;
        }
    }
    return NULL;
}

linkedlist_t *HashmapGetKeys(hashmap_t *map) {
    linkedlist_t *list = LinkedListCreate();
    for (int i = 0; i < map->tableSize; ++i) {
        for (int j = 0; j < map->table[i]->size; ++j) {
            element_t *element = (element_t *) LinkedListGetValue(map->table[i], j);
            LinkedListAdd(list, element->key);
        }
    }
    return list;
}

bool HashmapPut(hashmap_t *map, char *key, void *data) {
    if (HashmapContains(map, key)) {
        return false;
    }

    linkedlist_t *list = map->table[hash(map->tableSize, key)];

    // Allocate new hashmap element. On failure, return false.
    element_t *element = malloc(sizeof(element_t));
    if (element == NULL) {
        return false;
    }

    element->key = key;
    element->data = data;
    LinkedListAdd(list, element);
    return true;
}

bool HashmapRemove(hashmap_t *map, char *key) {
    if (HashmapContains(map, key)) {
        return false;
    }

    linkedlist_t *list = map->table[hash(map->tableSize, key)];
    for (int i = 0; i < list->size; ++i) {
        element_t *element = (element_t *) LinkedListGetValue(list, i);
        if (strcmp(element->key, key) == 0) {
            LinkedListRemoveIndex(list, i);
            return true;
        }
        free(element);
    }

    return false;
}

bool HashmapContains(hashmap_t *map, char *key) {
    linkedlist_t *list = map->table[hash(map->tableSize, key)];
    for (int i = 0; i < list->size; ++i) {
        element_t *element = (element_t *) LinkedListGetValue(list, i);
        if (strcmp(element->key, key) == 0) {
            return true;
        }
    }
    return false;
}

void HashmapFree(hashmap_t *map) {
    for (int i = 0; i < map->tableSize; ++i) {
        linkedlist_t *list = map->table[i];
        if (list != NULL) {
            // Free all hashmap elements in the list
            for (int j = 0; j < list->size; ++j) {
                element_t *element = LinkedListGetValue(list, j);
                free(element);
            }

            LinkedListFree(list);
        }
    }
    free(map->table);
    free(map);
}


static unsigned hash(size_t M, char *key) {
    int h;
    
    for (h = 0; *key != '\0'; key++) {
        h = (A*h + *key) % M;
    }
    
    return h;
}