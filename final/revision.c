#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

int main () {









}





/*
char * concat (char *s1, char *s2);
#include <stdio.h> 
#include <stdlib.h> 

#define MAX_STR 1000

char * concat (char * s1, char * s2);
int main (int argc, char * argv[]) {
    
    char s1[MAX_STR];
    char s2[MAX_STR];

    if (scanf ("%s %s", s1, s2) == 2) {
        char * s = concat (s1, s2);
        printf ("%s + %s = %s\n", s1, s2, s);
        free (s);
    } else {
        printf ("Couldn't scan in 2 numbers\n");
    }

    return 0;
}
char * concat (char *s1, char *s2) {
    
    int len1 = 0;
    while (*(s1 + len1) != 0) {
        
        len1++;
    }
    int len2 = 0;
    while (*(s2 + len2) != 0) {
        len2++;
    }
    char *new = malloc((len1 + len2 + 1) * sizeof(char));
    int i = 0;
    while (*s1 != 0) {
        new[i] = *s1;
        i ++;
        s1++;
    }
    while (*s2 != 0) {
        new[i] = *s2;
        i++;
        s2++;
    }

    new[i] = 0;
    return new;
}*/
/*int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage:%s <infile><outfile>", argv[0]);
        return 1;
    }
    FILE *p = fopen(argv[1], "r");
    int n;
    fscanf(p, "%d", &n);
    int line1[n];
    int line2[n];
  
    int dot_product = 0;
    int i = 0;
    while (i < n) {
        fscanf(p, "%d", &line1[i]);
        i++;
    }
    i = 0;
    while (i < n) {
        fscanf(p, "%d", &line2[i]);
        i++;
    }
    i = 0;
    while (i < n) {
        dot_product  = dot_product+ line1[i]* line2[i];
       // printf("line1[%d] = %d\n", i, line1[i]);
        i++;
    }
    FILE *output = fopen(argv[2], "w+");
    fprintf(output,"%d", dot_product);
    return 0;
}*/

/*int main () {
    int size;
    scanf("%d", &size);
    int i = 0;
    while (i < 2 * size - 1) {
        int j = 0;
        while (j < 2 * size - 1) {
            if ((i < size && j < size) && (i + j >= size - 1)) {
                printf("#");
            } else if (i >= size && j >= size && i + j <  3 *(size - 1) + 1) {
                printf("#");
            } else if (i < size && j >= size && j - i < size) {
                printf("#");
            } else if (i >= size && j < size && i - j < size) {
                printf("#");
            } else {
                printf(" ");
            }
            j++;
        }
        i++;
        printf("\n");
    }
    
    int c = fgetc(stdin);
    while (c != EOF) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        } else if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        putchar(c);
        c = fgetc(stdin);
    }
    int c;
    int array[MAX] = {0};
    scanf("%d", &c);
    array[c]++;
    int no_read = scanf("%d", &c);
    while (no_read == 1) {
        array[c] ++;
        if(array[c] == 2) {
            printf("%d is repeated.\n", c);
            return 0; 
        }
        no_read = scanf("%d", &c);
    }
    return 0;
}*/


