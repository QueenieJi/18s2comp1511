#include <stdio.h>

int main () {
	int i;
	int noRead = scanf("%d", &i);
	int even[1000] = {0}; 
	int n = 0;
	while (noRead == 1) {
		if (i % 2 == 0) {
			even[n] = i;
			n++;
		}
		noRead = scanf("%d", &i);
	}
	n = 0;
	while (even[n + 1] != 0) {
		printf("%d ", even[n]);
		n ++;
	}
	if (even[n] % 2 == 0 && even[n] != 0) {
		printf("%d\n", even[n]);
	} else {
		printf("\n");
	}
	return 0;
}
