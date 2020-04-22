#include <stdio.h>

int gcdRec (int a, int b);
int main () {
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	int result = gcdRec(a, b);
	printf("%d\n", result);
	return 0;
}

int gcdRec (int a, int b) {
	if (b == 0) {
		return a;
	}
	int r = a % b;
	if (r == 0) {
		if (a < b) {
			return a;
		} else {
			return b;
		}
	} else{
		a = gcdRec(b, r);
	
	}
	return a;
}
