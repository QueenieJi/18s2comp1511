#include <stdio.h>

int main() {
	int num,i,j,size;
	printf("How many boxes: ");
	scanf("%d", &num);
	i = 0;
	size = 4 * num - 1;
	while (i < size) {
		j = 0;
		while ( j < size) {
			if ( i % 2 != 0 && j >= i && j <= size -1 - i){
				printf(" ");
			} else if ( j % 2 != 0 && i >= j && i < size -1 - j){
				printf(" ");
			}else if ( i % 2 != 0 && j <= i && j >= size -1 - i){
				printf(" ");
			}else if ( j % 2 != 0 && i <= j && i >= size -1 - j){
				printf(" ");
			} else {
				printf("#");
			}
			j++;
		}
		i++;
		printf("\n");	
	}
	return 0;
}
