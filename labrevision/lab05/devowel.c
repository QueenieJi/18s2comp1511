#include <stdio.h>

int main() {
	int ch = getchar();
	while (ch != EOF) {
		
		if (ch != 'a' && ch != 'e' && ch != 'o' && ch != 'i' && ch != 'u') {
			putchar(ch);
		}
		ch = getchar();
	}
	return 0;
 
}


