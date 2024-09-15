#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fptr;

typedef struct Node {
    char *word;
    struct Node *prev;
    struct Node *next;
} Node;

Node *createNode(char *word){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->prev = NULL;   
    newNode->next = NULL;
    return newNode;
}

void *pushNode(Node **head, char *word){
    Node *newNode = createNode(word);

    if (*head == NULL){
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void printListReverse(Node *head){
    Node *temp = head;

    if (temp == NULL){
        printf("Lista vacia.");
        return;
    }

    while (temp->next !=NULL)
    {
        temp = temp->next;
    }

    while (temp != NULL)
    {
        printf("%s", temp->word);
        temp = temp->prev;
        printf("\n");
    }
}


int main(int argc, char *argv[]) {
    Node *head = NULL;

    pushNode(&head, "Hello");
    pushNode(&head, "World");

    printListReverse(head);

    if (argc == 1){
    } else if (argc == 2)
    {
    } else if (argc == 3)
    {
    }
}