#include <stdio.h>
#include <stdlib.h>

unsigned long long int printWondrous(unsigned long long int num);


int main (int argc, char *argv[]) {
    // Get the number.
    unsigned long long int number = 1;
    unsigned long long int count = printWondrous(number);

    while (count < 1234){
        unsigned long long int count = printWondrous(number);
        number ++;
    }
    
    printf(" %lld.\n", number);
    
    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

unsigned long long int printWondrous(unsigned long long int num) {
    unsigned long long int i = num;
    
    unsigned long long int count = 1;
    while(i != 1) {
        if(i % 2 == 0) {
            i = i / 2;
            
        }
        else {
            i = 3 * i + 1;
            
        }
        count ++;
    }
    
    // PUT YOUR CODE HERE

    return count; // CHANGE THIS TO YOUR RETURN VALUE
}
