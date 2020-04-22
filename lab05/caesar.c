#include <stdio.h>
#include <stdlib.h>



int encrypt(int character,int shift);

int main(int argc, char *argv[]) {
    
    int shift = atoi(argv[1]);
    int cha = getchar();
    while (cha  != EOF) {
        int new_cha = encrypt(cha,shift); 
        putchar(new_cha);
        cha = getchar();
    }
    return 0;
}

int encrypt(int character,int shift) {
    int new_cha = character;
    if (character >= 'a' && character <= 'z') {
        new_cha = (character - 'a'+ shift % 26 + 26) % 26 + 'a';
    }   
    else if (character >= 'A' && character <= 'Z') {
        new_cha = (character - 'A'+ shift % 26 + 26) % 26 + 'A';
    }     
    
    return new_cha;
}


    
