#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


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

void traverse(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s\n", current -> data);
        current = current -> next;
    }
}

void freeNode(struct Node* aNode) {
    if(aNode == NULL) {
        return;
    }
    free(aNode -> data);
    free(aNode);
}

void freeList(struct Node** head) {
    if(head == NULL || *head == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* nextNode;
    while(current != NULL) {
        nextNode = current -> next;
        freeNode(current);
        current = nextNode;
    }
    *head = NULL;
}