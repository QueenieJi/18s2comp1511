#include <stdio.h>

int main () {
	int year = 0;
	printf("Enter year: ");
	scanf("%d", &year);
	int a,b,c,d,e,f,g,h,i,j,k,l,m,p,date;
	a=year%19;
	b=year/100;
	c=year%100;
	d=b/4;
	e=b%4;
	f=(b+8)/25;
	g=(b-f+1)/3;
	h=(19*a+b-d-g+15)%30;
	i=c/4;
	k=c%4;
	l=(32+2*e+2*i-h-k)%7;
	m=(a+11*h+22*l)/451;
	p=(h+l-7*m+114)%31;
	date = p + 1;
	if ((h + l - 7 * m + 114) / 31 == 3) {
		printf("Easter is in March %d in %d.\n", date, year);
	}else {
		printf("Easter is in April %d in %d.\n", date, year);
	}
	return 0;
}
