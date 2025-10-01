// include the "LinkedList.h" file so we can reference it's function prototypes
#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


// creates a new node with a copy of the given string
//
// parameter data is the string to store in the node
//
// returns pointer to the newly created node or NULL if allocation fails
//
struct Node* createNode(char* data) {
    struct Node *newNode = malloc(sizeof(struct Node));
    // malloc check
    if(newNode == NULL) {
        return NULL;
    }
    newNode -> data = (char *)malloc(strlen(data) + 1);
    // check again
    if(newNode -> data == NULL) {
        free(newNode);
        return NULL;
    }


    strcpy(newNode -> data, data);
    newNode -> next = NULL;

    return newNode;
}


// inserts a node at the end of the single linked list
//
// parameter head is a pointer to the head pointer of the linked list
// parameter newNode is the node to insert
//
void insertAtEnd(struct Node** head, struct Node* newNode) {
    // if head or new node don't exist
    if(head == NULL || newNode == NULL)  {
        return;
    }

    // if there is no current head, set new node to be head
    if(*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while(current -> next != NULL) {
        current = current -> next;
    }
    current -> next = newNode;
}


// creates a linked list by reading lines from one of our test files
//
// parameter inf opens file pointer to read file given
//
// returns head of the created single linked list or NULL if an error occurs
//
struct Node* createList(FILE* inf) {
    if(inf == NULL) {
        return NULL;
    }

    char fileLine[MAX_LINE_SIZE];
    struct Node* head = NULL;

    while(fgets(fileLine, MAX_LINE_SIZE, inf)) {
        // stripping newlines
        fileLine[strcspn(fileLine, "\n")] = '\0';

        struct Node* newNode = createNode(fileLine);
        if(newNode == NULL) {
            freeList(&head);
            return NULL;
        }
        insertAtEnd(&head, newNode);
    }
    return head;
}


// removes a node at a given index from the singly linked list
//
// parameter head is a pointer to the head pointer of the linked list
// paramter index is the position of the node to remove
//
// returns the removed Node or NULL if invalid
//
struct Node* removeNode(struct Node** head, int index) {
    if(head == NULL || *head == NULL || index < 0) {
        return NULL;
    }

    struct Node* current = *head;

    // special case to check if we need to remove head of the linked list
    if(index == 0) {
        *head = current -> next;
        current -> next = NULL;
        return current;
    }

    struct Node* prev = NULL;
    int i = 0;
    while(current != NULL && i < index) {
        prev = current;
        current = current -> next;
        i++;
    }

    // index out of bounds check
    if(current == NULL) {
        return NULL;
    }

    prev -> next = current -> next;
    current -> next = NULL;
    return current;
}

// traverses the list and prints each node's data in the list
//
// parameter head is the head of the list
//
// no return value as it just prints out the list to see visually
void traverse(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s\n", current -> data);
        current = current -> next;
    }
}

// frees the memory for a single node
//
// parameter aNode is the node that has been chosen to be freed
//
// no return value as it just frees memory
void freeNode(struct Node* aNode) {
    if(aNode == NULL) {
        return;
    }
    free(aNode -> data);
    free(aNode);
}

// frees an entire linked list and also sets head to NULL
//
// parameter head is a pointer to the head pointer of the list
//
// returns nothing is list is already freed in memory
void freeList(struct Node** head) {
    if(head == NULL || *head == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* nextNode;

    // frees entire list by checking if another "current" node exists
    while(current != NULL) {
        nextNode = current -> next;
        freeNode(current);
        current = nextNode;
    }
    *head = NULL;
}