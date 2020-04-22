// Print Wondrous
// Created by
//  ... (z0000000)
//  ... (z0000000)
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
    int count = 1;
	printf("%d ", num);
	while (num != 1) {
	
		if (num % 2 == 0)  {
			num = num / 2;
		} else {
			num = 3 * num + 1;
		}
		printf("%d ",num);
		count ++;
	}
	printf("\n");
    return count; // CHANGE THIS TO YOUR RETURN VALUE
}
