#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LENGTH 100

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

void tokenToNode(char *userInput, Node **head){
    char *token = strtok(userInput, " ");
    while (token != NULL)
    {
        pushNode(head, token);
        token = strtok(NULL, " ");
    }
}

int main(int argc, char *argv[]) {
    Node *head = NULL;
    if (argc == 1){
        char userInput[MAX_INPUT_LENGTH];
        printf("Ingrese el texto a revertir: \n");
        
        if (fgets(userInput, MAX_INPUT_LENGTH, stdin) != NULL){
            size_t length = strlen(userInput);
            if (userInput[length - 1] == '\n') {
                userInput[length - 1] = '\0';
            }
            tokenToNode(userInput, &head);
        }
        printListReverse(head);
    } else if (argc == 2)
    {
        fptr = fopen(argv[1], "r");

        if (fptr == NULL){
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");   
        }


    } else if (argc == 3)
    {
        fptr = fopen(argv[1], "r");

        if (fptr == NULL){
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");   
        }
    } else if (argc >= 4)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");   
    }
    exit(1);
}