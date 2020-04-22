#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LINE 4096



int main(int argc, char *argv[]) {
	
	char string[4096];
	printf("Enter a string: ");
	int i = 0;
	while (i < 4096) {
		string[i] = 0;
		i++;
	}
	fgets(string,4096,stdin);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n') {
		printf("%c\n",string[i]);
		i++;
		
	}
		
	return 0;
}
