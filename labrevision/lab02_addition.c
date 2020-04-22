#include <stdio.h>

int main() {
	int m,n;
	printf("Please enter two integers: ");
	scanf("%d %d", &m,&n);
	int sum = m + n;
	printf("%d + %d = %d\n", m, n, sum);
	return 0;
}
