// Print the first n lines of a file
// written by Andrew Taylor andrewt@cse.unsw.edu.au
// April 2018 as a COMP1511 lab exercise
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_NLINES 10
#define MAX_LINE_LENGTH 1024

void print_first_n_lines(FILE *stream, int n_lines);
void print_first_n_lines1(FILE *stream, int n_lines);


int main(int argc, char *argv[]) {
    int n_lines;
    char *filename;

    if (argc == 2) {
        n_lines = DEFAULT_NLINES;
        filename = argv[1];
    } else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
        n_lines = atoi(argv[2]);
        filename = argv[3];
    } else {
        fprintf(stderr, "Usage: first_lines [-n lines] <file>");
        return 1;
    }

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror(filename);
        exit(1);
    }

    print_first_n_lines(f, n_lines);

    fclose(f);
    return 0;
}

void print_first_n_lines(FILE *stream, int n_lines) {
    int lines = 0;
    while (lines < n_lines) {
        int ch = fgetc(stream);
        if (ch == EOF) {
            return;
        }
        putchar(ch);
        if (ch == '\n') {
            lines = lines + 1;
        }
    }
}

// Alternative version using fgets
// - has the disadvantage of a maximum line length.
void  print_first_n_lines1(FILE *stream, int n_lines) {
    char line[MAX_LINE_LENGTH + 2];
    int lineNumber = 0;
    while (lineNumber < n_lines && fgets(line, MAX_LINE_LENGTH, stream) != NULL) {
        lineNumber = lineNumber + 1;
        fputs(line, stdout);
    }
}
