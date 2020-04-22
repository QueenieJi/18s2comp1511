#include <stdio.h>
#include <stdlib.h>

//created by Mitchell Shelton
//Modified by <you>

void printStaircase(int size);

int main(int argc, char *argv[]) {
    //Do not modify main

    if (argc != 2) {
        printf("Usage: ./q1 size\n");
        exit(1);
    }
    
    
    printStaircase(atoi(argv[1]));
    return 0;
}

//Given a size (e.g 8)
//Should print a staircase like this:


//       J
//      HI
//     EFG
//    ABCD
//   VWXYZ
//  PQRSTU
// IJKLMNO
//ABCDEFGH
void printStaircase(int size) {
    int i = 0;
    int start = ((size + 1) * size / 2 ) % 26 + 'A' - 1;
    
    while (i < size) {
        int j = 0;
        while (j < size) {
            if (i >= size - 1 - j) {
                start = start - i + (size - 1 - j);
                printf("%c", start);
            } else {
                printf(" ");
            }
            j++;
        }
        printf("\n");
        i++;
    }
}
