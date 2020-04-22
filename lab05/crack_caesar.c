#include <stdio.h>
#include <stdlib.h>



int encrypt(int character);

int main(int argc, char *argv[]) {
    
    int argument = 1;
    
    FILE *stream = fopen(argv[argument], "r");
        if (stream == NULL) {
            perror(argv[argument]);  // prints why the open failed
            return 1;
        }

        // fgetc returns next the next byte (ascii code if its a text file)
        // from a stream
        // it returns the special value EOF if not more bytes can be read from the stream

        int c = fgetc(stream);

        // return  bytes from the stream (file) one at a time
		
        while (c != EOF && (argument < 10000)) {
            int new_cha = encrypt(c); 
        	
        	
			fputc(new_cha, stdout); // write the byte to standard output
            c = fgetc(stream);
			
        }

        argument = argument + 1;
    
    return 0;
}

int encrypt(int character) {
    int new_cha = character;
    if (character >= 'a' && character <= 'z') {
        new_cha = (character - 'a'+ 9 % 26 + 26) % 26 + 'a';
    }   
    else if (character >= 'A' && character <= 'Z') {
        new_cha = (character - 'A'+ 9 % 26 + 26) % 26 + 'A';
    }     
    
    return new_cha;
}

