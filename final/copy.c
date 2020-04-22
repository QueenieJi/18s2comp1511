#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (argc != 3) {
        perror(argv[0]);
        return 1;
    }
    
        printf("Hi there");
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror(argv[1]);
        return 1;
    }
    
    FILE *output = fopen(argv[2], "a");
    if (output == NULL) {
        perror(argv[2]);
        return 1;
    }
    
    int c = fgetc(input);
    while (c != EOF) {
        fputc(c, output);
        c = fgetc(input);
    }
    fclose(output);



    return 0;
}
