#include <stdio.h>

#define MONEY 10

int main() {
	int scoop = 0;
	int per = 0;
	printf("How many scoops?");
	scanf("%d", &scoop);
	printf("How many dollars does each scoop cost?");
	scanf("%d", &per);
	if ( scoop*per <= MONEY) {
		printf("You have enough money!\n");
	} else {
		printf("Oh no, you don't have enough money :(\n");
	}
	return 0;
}
