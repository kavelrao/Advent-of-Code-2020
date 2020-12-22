#include "linkedlist.h"

linkedlist_t *LinkedListCreate() {
    linkedlist_t *result = malloc(sizeof(linkedlist_t));
    if (result == NULL) {
        return false;
    }
    result->root = NULL;
    result->size = 0;
    return result;
}

node_t *LinkedListGetNode(linkedlist_t *list, size_t index) {
    // Ensures the list is non-null, and index is in the valid range of 0 < index < size - 1.
    if (list == NULL || index >= list->size || index < 0) {
        return NULL;
    }

    // Traverse through the list until reaching the node of the given index.
    node_t *current = list->root;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    
    return current;
}

void *LinkedListGetValue(linkedlist_t *list, size_t index) {
    // Ensures the list is non-null, and index is in the valid range of 0 < index < size - 1.
    if (list == NULL || index >= list->size || index < 0) {
        return NULL;
    }

    // Traverse through the list until reaching the node of the given index.
    node_t *current = list->root;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    
    return current->data;
}

bool LinkedListInsert(linkedlist_t *list, void *data, size_t index) {
    // Ensure the list is non-null, and index is in the valid range of 0 < index < size.
    if (list == NULL || index > list->size || index < 0) {
        return false;
    }

    node_t *newNode = malloc(sizeof(node_t));
    if (newNode == NULL) {
        return false;
    }
    newNode->data = data;

    // If index == 0, we need to replace the list root node.
    if (index == 0) {
        if (list->root != NULL) {
            list->root->prev = newNode;
        }
        newNode->next = list->root;
        newNode->prev = NULL;
        list->root = newNode;
    }

    else {
        node_t *current = list->root;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        newNode->next = NULL;
        if (index != list->size) {
            newNode->next = current->next;
            current->next->prev = newNode;
        }
        newNode->prev = current;
        current->next = newNode;
    }
    
    list->size++;
    return true;
}

bool LinkedListAdd(linkedlist_t *list, void * data) {
    if (list == NULL) {
        return false;
    }

    return LinkedListInsert(list, data, list->size);
}

bool LinkedListContainsNode(linkedlist_t *list, node_t *node) {
    if (list == NULL || node == NULL) {
        return false;
    }

    node_t *current = list->root;
    while (current != NULL) {
        if (current == node) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool LinkedListContainsValue(linkedlist_t *list, void *data) {
    if (list == NULL) {
        return false;
    }

    node_t *current = list->root;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool LinkedListRemoveNode(linkedlist_t *list, node_t *node) {
    if (!LinkedListContainsNode(list, node)) {
        return false;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (list->root == node) {
        list->root = node->next;
    }

    list->size--;

    free(node);
    return true;
}

bool LinkedListRemoveIndex(linkedlist_t *list, size_t index) {
    node_t *node = LinkedListGetNode(list, index);
    if (node == NULL) {
        return false;
    }

    return LinkedListRemoveNode(list, node);
}

void LinkedListFree(linkedlist_t *list) {
    while (list->root != NULL) {
        LinkedListRemoveNode(list, list->root);
    }

    free(list);
}