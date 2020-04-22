#include <stdio.h>

int main() {
	int num;
	printf("Enter number :");
	int noread = scanf("%d", &num);
	int outliers = 0;
	
	while (noread == 1 ) {
		if (num < 5 || num > 25) {
			outliers++;
		}
		printf("Enter number: ");
		noread = scanf("%d", &num);
	}
	printf("\nOutliers: %d\n", outliers);

	return 0;
}
