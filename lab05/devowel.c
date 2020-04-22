#include <stdio.h>

int main() {
    int c;
    while( (c = getchar()) != EOF) {
        if ((c != 'a')&&(c != 'e')&&(c != 'i')&&(c != 'o')&&(c != 'u')) {
            putchar(c);
        }
      
    }
    return 0;
}
