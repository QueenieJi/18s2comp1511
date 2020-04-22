#include <stdio.h>
int main (){
	int num;
	scanf("%d", &num);
	if (num==1){
		printf("Please enter an integer: You entered one.\n");
	}
	else {
		if (num==2){
			printf("Please enter an integer: You entered two.\n");
		}
		else {
			if (num==3){
				printf("Please enter an integer: You entered three.\n");
			}
			else {
				if(num==4){
					printf("Please enter an integer: You entered four.\n");
				}
				else {
					if(num==5){
						printf("Please enter an integer: You entered five.\n");
					}
					else {
						if (num<=0){
							printf("Please enter an integer: You entered a number less than one.\n");
}
else{
printf("Please enter an integer: You entered a number greater than five.\n");
}
						}
					}
				}
			}
		}				
return 0;
}
