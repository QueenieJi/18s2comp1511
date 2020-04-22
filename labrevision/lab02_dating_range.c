#include <stdio.h>

int main () {
	int age = 0;
	printf ("Enter your age: ");
	scanf("%d", &age);
	int up = (age - 7)*2;
	int low = age / 2 +7;
	if (age <= low) {
		printf ("You are too young to be dating.\n");
	} else {
		printf ("Your dating range is %d to %d years old.\n", low, up);
	}
	
	return 0;
}
