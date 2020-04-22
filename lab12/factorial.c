#include <stdio.h>

long long factorial(long long n);
int main() {
	long long n = 0;
	scanf("%lld",&n);
	n = factorial(n);
	printf("%lld\n",n);
	return 0;
}

long long factorial(long long n) {
	if (n == 0) {
		return 1;
	}
	long long fac = 0;
	if (n >= 1) {
		fac = n * factorial(n - 1);
	}
	return fac;
}
