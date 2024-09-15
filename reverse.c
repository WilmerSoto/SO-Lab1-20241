#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
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
    size_t length = strlen(userInput);
    if (userInput[length - 1] == '\n') {
        userInput[length - 1] = '\0';
    }

    char *token = strtok(userInput, " ");
    while (token != NULL)
    {
        pushNode(head, token);
        token = strtok(NULL, " ");
    }
}

int hardlinkCheck(const char *file1, const char *file2) {
    struct stat stat1, stat2;

    if (stat(file1, &stat1) != 0) {
        return 0;
    }

    if (stat(file2, &stat2) != 0) {
        return 0;
    }
    return (stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev);
}

int main(int argc, char *argv[]) {
    Node *head = NULL;
    char userInput[MAX_INPUT_LENGTH];

    if (argc == 1){
        printf("Ingrese el texto a revertir: \n");
        
        if (fgets(userInput, MAX_INPUT_LENGTH, stdin) != NULL){
            tokenToNode(userInput, &head);
        }
        printListReverse(head);
        exit(0);
    } else if (argc == 2)
    {
        fptr = fopen(argv[1], "r");
        if (fptr == NULL){
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");   
            exit(1);
        }
        
        while (fgets(userInput, MAX_INPUT_LENGTH, fptr))                
        {   
            tokenToNode(userInput, &head);
        }
        printListReverse(head);
        exit(0);
    } else if (argc == 3)
    {
        if (strcmp(argv[1], argv[2]) == 0 || hardlinkCheck(argv[1], argv[2])){
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);   
        } 

        fptr = fopen(argv[1], "r");
        if (fptr == NULL){
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n");
            exit(1);   
        }
    } else if (argc >= 4)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");   
    }
    exit(1);
}