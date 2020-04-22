#include <stdio.h>
int main (){
	printf("Enter size: ");
	int n,j;
	scanf("%d", &n);
	int i = 0;
	
	while (i<n){
		j=0;
		
		while (j<n){
			if ((j==i)||(j==(n-i-1))){

				printf("*");
			}
			else { printf("-");
			}
		j++;
		}
		printf("\n");
		i ++;
	}
	return 0;
}
	
