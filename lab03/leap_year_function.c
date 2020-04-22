#include <stdio.h>

int isLeapYear(int year);

int main (){
	int year = 0;
	scanf("%d", &year);
	if (isLeapYear (year) == 1){
		printf("Enter year: %d is a leap year", year);
	}
	else {
		printf("Enter year: %d is not a leap year", year);
	}
return 0;
}

int isLeapYear(int year){
	if (year%4 != 0){
		return 0;
	}
	else if(year%100 != 0){
		return 1;
	}
	else if(year%400 != 0){
		return 0;
	}
	else {
		return 1;
	}
}
