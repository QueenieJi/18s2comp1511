#include <stdio.h>

int main () {
	int i;
	int noRead = scanf("%d", &i);
	int list[1000] = {0}; 
	int n = 0;
	int counter = 0;
	while (noRead == 1) {
		list[n] = i;
		n++;
		noRead = scanf("%d", &i);
		counter ++;
	}
	n = 0;
	int m = 0;
	while (list[n] != 0) {
		if (list[counter - 1] == list[n]) {
		m ++; 
		}
		n++;
	}
	printf("%d\n", m);
	return 0;
}
