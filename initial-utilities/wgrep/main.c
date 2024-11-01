#include <stdio.h>
#include <string.h>

int word_in_line(char* word, char* line) {
    int j = 0;
    for (int i=0;i<strlen(line);i++) {
        if (line[i] == word[j]) {
            j += 1;
            if (j >= strlen(word)) {
                return 1;
            }

        }
        else {
            j = 0;
        }
    }
    return 0;
}

void grep(FILE* fp, char* search_term) {
    char line[256];
    while (fgets(line, sizeof line, fp) != NULL) {
        if (word_in_line(search_term, line)) {
            printf("%s", line);
        }
    }
}

int main(int argc, char * argv[]) {
    int num_args = argc - 1;
    if (num_args == 0) {
        fprintf(stdout, "wgrep: searchterm [file ...]\n");
        return 1;
    }

    char* search_term = argv[1];
    if (num_args == 1) {
        grep(stdin, search_term);
    }
    for (int i=2;i<argc;i++) {
        char* filename = argv[i];
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stdout, "wgrep: cannot open file\n");
            return 1;
        }
        grep(fp, search_term);
    }
    return 0;
}