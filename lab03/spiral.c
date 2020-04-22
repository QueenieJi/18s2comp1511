#include <stdio.h>

int main(){
	int n,i,j;
	scanf("%d",&n);
	printf("Enter size: ");
	i=1;
	while (i<= n){
		j=1;
		while (j<=n){
			if ((i%2!=0)&&(j>=(i-2))&&(j<=(n-i+1))&&(i>=3)){
				printf("*");
			}
			else if (i==1){
				printf("*");
			}
			else if ((j%2 !=0)&&(i<=j)&&(i>=(n-j+1))){
				printf("*");
			}
			else if ((i%2 !=0)&&(j<=i)&&(j>=n-i+1)){
				printf("*");
			}
			else if ((j%2 !=0)&&(i<=(n-j+1))&&(i>=(j+3))){
				printf("*");
			}
			else {
				printf("-");
			}
		
		j++;
	}
	printf("\n");
	i++;
	}
return 0;
}
	

