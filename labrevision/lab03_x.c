#include <stdio.h>

int main () {
	int i,j;
	int size = 0;
	printf("Enter size: ");
	scanf("%d", &size);
	i = 0;
	while ( i < size) {
		j = 0;
		while (j < size) {
		if ( j == i || j == size - 1 - i) {
			printf("*");
		} else {
			printf("_");
		}
		j++;
		}
		printf("\n");
		i++;
	}	
	return 0;
}
