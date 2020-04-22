#include <stdio.h>
int main(){
	int a=0;
	int b=0;
	int c=0;
	
	scanf("%d", &a);
	
	scanf("%d", &b);
	
	scanf("%d", &c);
	if ((a>b)&&(b>c)) {
		printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",c,b,a);
	}
	else {
		if ((a>=c)&&(c>=b)){
			printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",b,c,a);
		}
		else {
			if((b>=c)&&(c>=a)){
				printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",a,c,b);
			}
			else {
				if ((b>=a)&&(a>=c)){
					printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",c,a,b);
				}
				else {
					if((c>=a)&&(a>=b)){
						printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",b,a,c);
					}
					else {
						printf("Enter integer: Enter integer: Enter integer: The integers in order are: %d %d %d\n",a,b,c);
					}
				}
			}
		}
	}
return 0;
}
	
	
