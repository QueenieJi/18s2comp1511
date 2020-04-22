#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 4096



int main(int argc, char *argv[]) {
	
	char string[MAX_LINE] = {0};
	printf("Enter a string: ");
	int i = 0;
	fgets(string,4096,stdin);
	int count = 0;
	while (string[i] != '\0' && string[i] != '\n') {
		i++;	
	}
	count = i - 1;
	
	char str_new[MAX_LINE] = {0};
	int j = 0;
	while (j <= count) {
		str_new[j] = string[count - j];
		
		j++;
	}
	
	int k = 0;
	while (string[k] == str_new[k] && k < count) {
		k++;
	}
	
	if (k == count || count == -1) {
		printf("String is a palindrome\n");
		
	} else {
		printf("String is not a palindrome\n");
	}	
	return 0;
}
