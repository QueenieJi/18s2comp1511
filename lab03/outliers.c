#include <stdio.h>
int main(){
	int number, noread;
	noread = scanf("%d", &number);
	int outliers = 0;
	while (noread == 1){
		if ((number<5)||(number>25)){
			outliers++;
			printf("Enter number: ");
		}
		else {
			printf("Enter number: ");
		}
	
	
	noread = scanf("%d", &number);
	}
	
	printf("Enter number: \nOutliers: %d\n",outliers);
return 0;
}
