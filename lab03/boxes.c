#include <stdio.h>
int main(){
	int n,i,j;
	scanf("%d", &n);
	printf("How many boxes: ");
	i = 1;
	while (i<=(-1+n*4)){
		j = 1;
		while (j<=(-1+4*n)){
			if((j%2==0)&&(i%2==0)){
				printf(" ");	
			}
			else if ((i%2==0)&&(j>=i)&&(j<=4*n-1-i)){
				printf(" ");
			}
			else if ((j%2 == 0)&&(i>=j)&&(i<=4*n-1-j)){
				printf(" ");
			}
			else if ((i%2 ==0)&&(j<i)&&(j>4*n-1-i)){
				printf(" ");
			}
			else if ((j%2 ==0)&&(i<j)&&(i>4*n-1-j)){
				printf(" ");
			}
			else{
				printf("#");
			}
		j++;
			
	}
	printf ("\n");
	i ++;
	}
return 0;
}

