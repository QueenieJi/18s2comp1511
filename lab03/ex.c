#include <stdio.h>
int main () {
	int length ,width ,area;
	printf("Please enter rectangle length: ");
	scanf("%d",&length);
	printf("\nPlease enter rectangle width: ");
	scanf("%d",&width);
	area = length * width;
	printf("\nArea = %d \n", area);
	
	return 0;
}
