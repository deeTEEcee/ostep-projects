#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[]) {
    int num_args = argc - 1;
    char* inputFile;
    char* outputFile;
    if (num_args > 2) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }
    else if (num_args == 2) {
        inputFile = argv[1];
        outputFile = argv[2];
    }
    else if (num_args == 1) {
        // TODO: Need to seek end of file and work our way backwards
        inputFile = argv[1];
        FILE* fp = fopen(inputFile, "r");
        if (fp == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", inputFile);
            return 1;
        }
//        while ((read = getline(&line, &len, fp)) != -1) {
//            printf("Retrieved line of length %zu:\n", read);
//            printf("%s", line);
//        }
    }
    else {
        char input[1000];
        while(fgets(input, sizeof input, stdin) != NULL) {
            printf("%s", input);
        }
    }
    return 0;
}