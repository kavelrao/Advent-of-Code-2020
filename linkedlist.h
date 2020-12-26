/*
 *    Functions for using linked lists.
 *    Implemented using a doubly linked list.
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Represents a single node in a linked list.
// Stores a pointer to previous node, pointer to next node, and void pointer to data field.
typedef struct node_st {
    struct node_st *prev;
    struct node_st *next;
    void *data;
} node_t;

// Represents a linked list.
// Stores a pointer to a root node and the size of the list.
typedef struct linkedlist_st {
    node_t *root;
    size_t size;
} linkedlist_t;

// Allocates a new linked list and returns a pointer to the list.
// Root node is initialized to NULL.
// The user must free the linked_list* using LinkedListFree.
linkedlist_t *LinkedListCreate();

// Returns a pointer to the node at the given index.
// If the index is out of the bounds 0 <= index < size, returns NULL.
node_t *LinkedListGetNode(linkedlist_t *list, size_t index);

// Returns a void pointer to the node at the given index.
// If the index is out of the bounds 0 <= index < size, returns NULL.
void *LinkedListGetValue(linkedlist_t *list, size_t index);

// Inserts an element with the given data into the given index of the list.
// Index must be in the bounds 0 <= index < size.
// Given data must be a pointer to the desired data value.
// Returns true for success.
bool LinkedListInsert(linkedlist_t *list, void *data, size_t index);

// Inserts an element with the given data at the end of the list.
// Index must be in the bounds 0 <= index < size.
// Given data must be a pointer to the desired data value.
// Returns true for success.
bool LinkedListAdd(linkedlist_t *list, void * data);

// Returns true if the given node is included in the list.
bool LinkedListContainsNode(linkedlist_t *list, node_t *node);

// Returns true if the given data value is included in the list.
bool LinkedListContainsValue(linkedlist_t *list, void *data);

// Returns true if the given string is included in the list.
// Should only be used when storing char* in the list.
bool LinkedListContainsString(linkedlist_t *list, char *string);

// Removes the given node from the list it's in.
// Returns true for success.
bool LinkedListRemoveNode(linkedlist_t *list, node_t *node);

// Removes the node from the given index in the list.
// Returns true for success.
bool LinkedListRemoveIndex(linkedlist_t *list, size_t index);

// Deletes all elements and the list, freeing all allocated memory.
// If necessary, the data fields of the nodes must be freed separately by the user.
void LinkedListFree(linkedlist_t *list);

#endif  // _LINKED_LIST_H_