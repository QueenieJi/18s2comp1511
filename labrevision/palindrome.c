#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main () {
	printf("Enter a string: ");
	char str[4000] = {0};
	fgets(str,4000,stdin);
	int length = 0;
	char new_str[4000] = {0};
	while ( length < 4000 && str[length] != '\0' && str[length] != '\n' ) {
		length++;
	}
	new_str[length] = str[length];
	length = length - 1;
	
	int i = 0;
	while ( i <= length){
		new_str[i] = str[length - i];
		
		i++;
	}
	if (strcmp(str,new_str) == 0){
		printf("String is a palindrome\n");	
	} else {
		printf("String is not a palindrome\n");
	}
	return 0;
}
