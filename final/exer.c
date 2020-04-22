/*#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 4096

void process_stream(FILE *stream, char stream_name[]);

int main(int argc, char *argv[]) {

    if (argc == 1) {
        // if no files are specified, process stdin
        process_stream(stdin, "<stdin>");
    } else {
        int argument = 1;
        while (argument < argc) {
            FILE *in = fopen(argv[argument], "r");
            if (in == NULL) {
                // perror could be used for a better error message here
                fprintf(stderr, "%s: open of '%s' failed\n", argv[0], argv[argument]);
                return 1;
            }

            process_stream(in, argv[argument]);

            argument = argument + 1;
        }
    }

    return 0;
}

void process_stream(FILE *stream, char stream_name[]) {
    int line_count = 0;
    int character_count = 0;
    int word_count = 0;

    int lastc = ' ';
    int c = fgetc(stream);

    while (c != EOF) {
        if (c == '\n') {
            line_count = line_count + 1;
        }
        if (isspace(c) && !isspace(lastc)) {
            word_count = word_count + 1;
        }
        character_count = character_count + 1;
        lastc = c;
        c = fgetc(stream);
    }

    if (!isspace(lastc)) {
            word_count = word_count + 1;
    }

    printf("%s contains %d lines %d words %d characters\n", stream_name, line_count, word_count, character_count);
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void process_stream(FILE *stream, char stream_name[]);
void process_stream2(FILE *stream, char stream_name[]);
int main (int argc, char *argv[]) {
    if (argc == 1) {
        process_stream2(stdin, "<stdin>");
    } else {
        int argument = 1;
        while (argument < argc) {
            FILE *str = fopen(argv[argument], "r");
            if(str == NULL) {
                perror(argv[argument]);
            }
            process_stream2(str, argv[argument]);
            argument++;
        }
    }
    return 0;
}
void process_stream2(FILE *stream, char stream_name[]) {
    int line_count = 0;
    int character_count = 0;
    int word_count = 0;
    char string[10000];
    while (fgets(string, 10000, stream) != NULL) {
        int i = 0;
        while (string[i] != '\0') {
            if (string[i] == '\n') {
                line_count++;
            }
            if (i > 0 && isspace(string[i]) && !isspace(string[i - 1])) {
                word_count++;
            }
            character_count++;
            i++;
       }
    }
    printf("There is %d characters, %d words, %d lines in file %s\n",
    character_count, word_count, line_count, stream_name);

}
void process_stream(FILE *stream, char stream_name[]) {
    int line_count = 1;
    int word_count = 0;
    int character_count = 0;
    int lastc = ' ';
    int c = fgetc(stream);
    while (c != EOF) {
        if (lastc == '\n') {
            line_count++;
            word_count++;
        } else if (lastc != ' ' && c == ' ') {
            word_count++;
        } else {
            character_count++;
        }
        lastc = c;
        c =fgetc(stream);
    }
    
    printf("There is %d characters, %d words, %d lines in file %s\n",
    character_count, word_count, line_count, stream_name);
}
