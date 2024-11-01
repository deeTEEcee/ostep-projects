#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>

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
    FILE* fp_in;
    FILE* fp_out = stdout;
    struct stat stat_in, stat_out;

    char buffer[256];
    Node* root = NULL;
    Node* current = root;
    assert(sizeof(current->value) >= sizeof(buffer));

    if (num_args > 2) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }
    else if (num_args == 2) {
        inputFile = argv[1];
        outputFile = argv[2];
        int dup_file = 0;
        if (strcmp(inputFile, outputFile) == 0) {
            dup_file = 1;
        }
        if (access(outputFile, F_OK) == 0) {
            // File already exists
            if (stat(inputFile, &stat_in) != -1 && stat(outputFile, &stat_out) != -1) {
                if (stat_in.st_ino == stat_out.st_ino) {
                    dup_file = 1;
                }
            }
        }
        if (dup_file == 1) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            return 1;
        }
        fp_in = fopen(inputFile, "r");
        fp_out = fopen(outputFile, "w");
    }
    else if (num_args == 1) {
        inputFile = argv[1];
        fp_in = fopen(inputFile, "r");
    }
    else {
        fp_in = stdin;
    }

    if (fp_in == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", inputFile);
        return 1;
    }

    while (fgets(buffer, sizeof buffer, fp_in) != NULL) {
        Node* new = (Node*) malloc(sizeof(Node));
        new->next = NULL;
        new->prev = NULL;
        if (current == NULL) {
            current = new;
            root = current;
            strcpy(current->value, buffer);
        }
        else {
            current->next = new;
            strcpy(new->value, buffer);
            new->prev = current;
            current = new;
        }
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