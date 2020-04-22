#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("nothing!\n");
    } else {
        int i = 1;
        while (i < argc) {
            fputs(argv[i], stdout);
            fputs(" ",stdout);
            i ++;
        }
    
    }
    return 0;
}
