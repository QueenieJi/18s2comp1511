#include <stdio.h>

int main () {
	int num = 0;
	printf ("Enter number: ");
	scanf("%d", &num);
	int i = 1;
	while ( i < num) {
		if (i % 3 == 0 || i % 5 == 0) {
			printf("%d\n", i);
		} 
		i++;
	}

	return 0;
}
