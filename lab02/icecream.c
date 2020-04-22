#include <stdio.h>

int main(){
	
	int a;
	int b;
	int total;
	scanf("%d",&a);
	
	scanf("%d", &b);
	total = a*b;
	if ((total<=10)){
		printf("How many scoops? How many dollars does each scoop cost?You have enough money!\n");
		}
	else {
		printf("How many scoops? How many dollars does each scoop cost?Oh no, you don't have enough money :(\n");
		}
return 0;
}
