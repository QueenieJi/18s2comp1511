#include <stdio.h>

int main() {
	int num = 0;
	scanf("%d", &num);
	if (num < 0) {
		printf("Don't be so negative!\n");
	} else if (num > 0) {
		printf("You have entered a positive number.\n");
	}
	else {
		printf("You have entered zero.\n");
	}

	return 0;
}
