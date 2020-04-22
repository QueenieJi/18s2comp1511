#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int change_to_upper(char str);

//int main () {
    /*char str1[10];
    char str2[10];
    fgets(str1, 10, stdin);
    fgets(str2, 10, stdin);
    if (strlen(str1) != strlen(str2)) {
        printf("1\n");
    } else {
        int i = 0;
        while (i < strlen(str1) && str1[i] == str2[i]) {
            i++;
        }
        if (i == strlen(str1)) {
            printf("2\n");
        } else {
            int j = 0;
            while (j < strlen(str1)) {
                str1[j] = change_to_upper(str1[j]);
                str2[j] = change_to_upper(str2[j]);
                if (str1[j] == str2[j]) {
                    j++;
                } else {
                    printf("4\n");
                    break;
                }
            }
            if (j == strlen(str1)) {
                printf("3\n");
            }
        }
    }*/
int G = 0;   /* a global variable, stored in BSS segment */
    
   int main(int argc, char **argv) {
    static int s;  /* static local variable, stored in BSS segment */
    int a;         /* automatic variable, stored on stack */
    int *p;        /* pointer variable for malloc below */
    /* obtain a block big enough for one int from the heap */
    p = malloc(sizeof(int));

    printf("&G   = %p\n", (void *) &G);
    printf("&s   = %p\n", (void *) &s);
    printf("&a   = %p\n", (void *) &a);
    printf("&p   = %p\n", (void *) &p);
    printf("p    = %p\n", (void *) p);
    printf("main = %p\n", (void *) main);

    free(p);

     return 0;
}

int change_to_upper(char str) {
    if (str <= 'z' && str >= 'a') {
        return str - 'a' + 'A';
    } else {
        return str;
    }
}
