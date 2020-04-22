#include <stdio.h>

int main() {
	int num = 0;
	scanf("%d", &num);
	if(num > 0) {
		printf("You have entered a positive number.\n");
	} else if (num == 0) {
		printf("You have entered zero.\n");
	} else {
		printf("Don't be nagative!\n");
	}
	return 0;
}
