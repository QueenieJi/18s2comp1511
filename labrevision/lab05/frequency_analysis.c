#include <stdio.h>
#include <stdlib.h>


int main() {
	int ch = getchar();
	int integer_counts[26] = {0};
	float sum = 0;
	while (ch != EOF) {
		if (ch >= 'a' && ch <= 'z'){
			ch = ch - 'a';
			integer_counts[ch]++;
			sum ++;
		} else if (ch >= 'A' && ch <= 'Z') {
			ch = ch - 'A';
			integer_counts[ch]++;
			sum ++;
		}
		ch = getchar();
	}	
	int i = 0;
	while (i < 26) {
		float fre = integer_counts[i] / sum;
		printf("'");
		putchar(i + 'a');
		printf("'");
		printf(" %f %d\n",fre,integer_counts[i]);
		i++;		
	}
	return 0;

}
