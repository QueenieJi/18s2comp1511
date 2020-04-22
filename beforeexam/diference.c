#include <stdio.h>

int main () {
	
    int noread;
	int sum = 0;
	int num1 = 0;
	noread = scanf("%d",&num1);
	int num2 = 0;
	//scanf("%d",&num2);
	int diference = 0;
    while (noread == 1) {
		scanf(" %d", &num2);
		diference = num1 - num2;
		printf("Diference is %d\n", diference);
		sum =  sum + diference;
		num1 = num2;
		printf("Sum is %d\n", sum);
	}
	return 0;
} 
