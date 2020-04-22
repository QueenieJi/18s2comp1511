#include <stdio.h>
int main(){
	int number = 0;
	printf("Enter number: ");
	scanf("%d", &number);
	int n = 1;
	while(n< number){
		if ((n%3==0)||(n%5)==0){
			printf("%d\n",n);
			n++;
		}
		else {
			n++;
		}
	}
return 0;
}
			
	


