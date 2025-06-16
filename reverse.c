#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
    struct Node *prev;
} Node;

void freeLinkedList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        head = temp->next;
        free(temp->data);
        free(temp);
        temp = head;
    }
}

int main (int argc, char *argv[]) {
    if (argc > 3) {
        fprintf(stderr, "Usage: <input_file> <output_file>\n");
        exit(1);
    }

    if (argc == 3 && strcmp(argv[1], argv[2]) == 0){
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    }

    FILE *inputFile;
    FILE *outputFile;
    if (argc >= 2){
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    } else {
        inputFile = stdin;
    }
    
    if (argc == 3) {
        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(inputFile);
            exit(1);
        }
    } else {
        outputFile = stdout;
    }
    
    Node *head = NULL, *tail = NULL;
    char *line = NULL;
    size_t len = 0;
    while(getline(&line, &len, inputFile) != -1){
        Node *newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            if (inputFile != stdin){
                fclose(inputFile);
            }
            if (outputFile != stdout) {
                fclose(outputFile);
            }
            freeLinkedList(head);
            exit(1);
        }
        newNode->data = strdup(line);
        if (newNode->data == NULL) {
            fprintf(stderr, "strdup failed\n");
            free(newNode);
            free(line);
            if (inputFile != stdin) {
                fclose(inputFile);
            }
            if (outputFile != stdout) {
                fclose(outputFile);
            }
            freeLinkedList(head);
            exit(1);
        }
        newNode->next = NULL;
        newNode->prev = tail;
        if (tail != NULL) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
    }
    free(line);
    if (inputFile != stdin){
        fclose(inputFile);
    }
    
    Node *current = tail;
    while(current != NULL){
        size_t len = strlen(current->data);
        if (len> 0 && current->data[len-1]== '\n'){
            current->data[len-1] = '\0';
        }
        if (current->prev != NULL){
            fprintf(outputFile, "%s\n", current->data);
        } else{
            fprintf(outputFile, "%s", current->data);
        }
        current = current->prev;
    }
    if (outputFile != stdout){
        fclose(outputFile);
    };
    freeLinkedList(head);
    return 0;
}