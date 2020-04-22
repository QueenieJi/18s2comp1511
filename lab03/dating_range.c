#include <stdio.h>
int main (){
	int age;
	printf("Enter your age:");
	scanf("%d", &age);
	int max;
	int min;
	min = age/2 +7;
	max = (age - 7)*2;
		if (min<max){
			printf("Your dating range is %d to %d years old.\n", min, max);
		}
		else {
			printf("You are too young to be dating.\n");
		}
return 0;
}
