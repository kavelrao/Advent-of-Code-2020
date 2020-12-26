/*
 *    Functions for using hash maps.
 *    Uses separate chaining to deal with collisions.
 */

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedlist.h"

// Constant for hash function determined by alphabet size.
#define A 128

// Initial table size variable. Must be prime.
#define INIT_SIZE 101

// Represents one key-value pair in the hash map.
typedef struct element_st {
    char *key;
    void *data;
} element_t;

// Represents a hashmap. 
// Stores a reference to a table of linked lists
// and a table size, which must be prime.
typedef struct hashmap_st {
    linkedlist_t **table;
    size_t tableSize;
} hashmap_t;

// Allocates a new hashmap and returns a pointer.
// The user must free the hashmap_t* with HashmapFree.
hashmap_t *HashmapCreate();

// Returns a pointer to the value associated with the given key.
// If the key is not in the map, returns NULL.
void *HashmapGet(hashmap_t *map, char *key);

// Returns a linked list containing all keys in the hashmap.
linkedlist_t *HashmapGetKeys(hashmap_t *map);

// Inserts an element with the given data into the given index of the list.
// Index must be in the bounds 0 <= index < size.
// Given data must be a pointer to the desired data value.
// Fails if key is already in the hashmap.
// Returns true for success.
bool HashmapPut(hashmap_t *map, char *key, void *data);

// If the key is contained in the hashmap, removes the key-value pair associated with the given key.
// Returns true for success.
bool HashmapRemove(hashmap_t *map, char *key);

// Returns true if the hashmap contains the given key.
bool HashmapContains(hashmap_t *map, char *key);

// Deletes all elements and the list, freeing all allocated memory.
// If necessary, the data fields of the nodes must be freed separately by the user.
void HashmapFree(hashmap_t *map);


#endif  // _HASH_MAP_H_