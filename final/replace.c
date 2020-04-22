#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 10000

void replace_pattern(char target[], char replacement[], char string[], int target_length);

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage:%s<target><replacement><file>", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[3], "r");
    if (file == NULL) {
        perror(argv[3]);
        return 1;
    }
    char string[MAX_LINE];    
    int len = strlen(argv[1]);
    while (fgets(string, MAX_LINE, file)) {
        replace_pattern(argv[1], argv[2], string, len);
    }
return 0;
}

void replace_pattern(char target[], char replacement[], char string[], int target_length) {
    int newlen = strlen(string) + strlen(replacement) + target_length;
    int i = 0;
    int j = 0;
    char newstr[MAX_LINE];
    while (string[i] != '\0' && j < newlen - 1) {
        if (strncmp(target, &string[i], target_length) == 0) {
            strncpy(&newstr[j], replacement, newlen);
            i = i + target_length;
            j = j + newlen;
        } else {
            newstr[j] = string[i];
            i++;
            j++;
        }
    }
    newstr[j] = '\0';
    printf("%s\n", newstr);

}
