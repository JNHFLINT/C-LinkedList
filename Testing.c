#include "Testing.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){

    //initialize file pointer to NULL 
    FILE *infile = NULL; 
    //Define a character array to store the name of the file to read and write
    char filename[MAX_LINE_SIZE];  
    //Prompt the user to input a filename and continue to prompt the user until they enter a correct one
    while(infile == NULL) {  
        printf("Enter filename: ");  
        scanf("%s",filename);
        //When given a filename, use fopen to create a new file pointer. 
            //If fopen can not find the file, it returns null
        infile = fopen(filename, "r+");
        if(infile == NULL){ 
            printf("ERROR: file %s cannot be opened\n", filename);
        }
    }

    //Test your linked list functions here!!!

        // ====== TESTING START ======
    printf("\n--- Creating list from file ---\n");
    struct Node* head = createList(infile);

    printf("\n--- Traversing list ---\n");
    traverse(head);

    printf("\n--- Removing node at index 0 (head) ---\n");
    struct Node* removed = removeNode(&head, 0);
    if (removed) {
        printf("Removed: %s\n", removed->data);
        freeNode(removed); // don’t forget to free it
    } else {
        printf("Remove failed!\n");
    }

    printf("\n--- Traversing list after removal ---\n");
    traverse(head);

    printf("\n--- Freeing list ---\n");
    freeList(&head);
    if (head == NULL) {
        printf("List successfully freed.\n");
    }

    // ====== TESTING END ======

    fclose(infile);

}
