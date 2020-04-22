// Print Wondrous
// Created by
//  Queenie (z5191512)
//  Tina (z5191511)
// Created on 2018-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

int printWondrous(int num);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {
    // Get the number.
    int number;
    printf ("Enter a number: ");
    scanf("%d", &number);

    // Call printWondrous and save the count.
    int count = printWondrous(number);

    printf("The count is %d.\n", count);

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

int printWondrous(int num) {
    int i = num;
    printf("%d ", i);
    int count = 1;
    while(i != 1) {
        if(i % 2 == 0) {
            i = i / 2;
            printf("%d ", i);
        }
        else {
            i = 3 * i + 1;
            printf("%d ",i);
        }
        count ++;
    }
    printf("\n");
    // PUT YOUR CODE HERE

    return count; // CHANGE THIS TO YOUR RETURN VALUE
}
