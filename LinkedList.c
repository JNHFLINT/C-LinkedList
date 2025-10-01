#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>


struct Node* createNode(char* data);
void insertAtEnd(struct Node** head, struct Node* newNode);

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