#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 10000

int check_prefix(char prefix[], char string[]);

int main (int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <prefix> <files>\n", argv[0]);
        return 1;
    }
        int argument = 2;
        while (argument < argc) {
            FILE *in = fopen(argv[argument], "r");
            if (in == NULL) {
                perror(argv[argument]);
                return 1;
            }
            char line[MAX_LINE];
            while (fgets(line, MAX_LINE, in) != NULL) {
                
                if(check_prefix(argv[1], line) == 0) {
                    printf("%s", line);
                }
            }
            fclose(in);
            argument++;
        }
    
    return 0;
}

int check_prefix(char prefix[], char string[]) {
    int lenth = strlen(prefix);
    return strncmp(prefix, string, lenth);
}


