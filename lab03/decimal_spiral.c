#include <stdio.h>

	
int main(){
	int i,j,n,number,m,x;
	scanf("%d", &n);
	i = 1;
	while (i<=n){
		
		j = 1;
		while (j<=n){
			if( (i%2 != 0)&&(j>=i-1)&&(j<=(n-i+1))){
				m = n - 2*(i - 1);
				number = ((m*m+2*m-1)/2 - j+i-1)%10;
				printf("%d", number);
			}
			//else if ((i%2 != 0)&&(j<=i)&&(j>=n-i+1)&&(i<=(n-2))){
			//	m = n - 2*(i - 1);
			//	number = (-(m*m+2*m-1)/2+ 2*n- i+j-9)%10;
			//	printf("%d", number);
			//}
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
