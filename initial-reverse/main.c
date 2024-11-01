#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node {
    char value[256];
    struct node* next;
    struct node* prev;
} Node;

void freeall(Node* root) {
    Node* current = root;
    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
        free(tmp);
    }
}

int main(int argc, char * argv[]) {
    int num_args = argc - 1;
    char* inputFile = NULL;
    char* outputFile = NULL;
    FILE* fp_out = NULL;

    if (num_args > 2) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }
    else if (num_args == 2) {
        inputFile = argv[1];
        outputFile = argv[2];
        fp_out = fopen(outputFile, "w");
    }
    else if (num_args == 1) {
        inputFile = argv[1];
        fp_out = stdout;
    }
    else {
        char input[1000];
        while(fgets(input, sizeof input, stdin) != NULL) {
            printf("%s", input);
        }
    }

    FILE* fp_in = fopen(inputFile, "r");
    if (fp_in == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", inputFile);
        return 1;
    }

    char buffer[256];
    Node* root = (Node*) malloc(sizeof(Node));
    root->next = NULL;
    root->prev = NULL;
    Node* current = root;
    assert(sizeof(current->value) >= sizeof(buffer));

    // Insert into linked list
    while (fgets(buffer, sizeof buffer, fp_in) != NULL) {
        strcpy(current->value, buffer);
        Node* new = (Node*) malloc(sizeof(Node));
        current->next = new;
        new->next = NULL;
        new->prev = current;
        current = new;
    }

    // Read in reverse
    while (current != NULL) {
        fprintf(fp_out, "%s", current->value);
        current = current->prev;
    }

    // Cleanup
    fclose(fp_in);
    if (outputFile) {
        fclose(fp_out);
    }
    freeall(root);
    return 0;
}