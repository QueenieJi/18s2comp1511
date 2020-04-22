#include <stdio.h>
#define size 10


int main () {
	int array[size] ;
	int i = 0;
	while (i < size - 1) {
		scanf ("%d", &array[i]);
		i++;
	}
	
	
	int num = 10;
	i = 0;
	while (i < size - 1) {
		
		if (array[i] < 10 && array[i] > num){
			num = array[i];
		}
		
	i++;
	}
	printf("The closest number of limit 10 is %d\n",num);
	return 0;
}
