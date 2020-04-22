#include <stdio.h>
int main(){
int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
int year;
int easter_Month;
int easter_Date;

scanf("%d",&year);
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
easter_Month =(h+l-7*m+114)/31; 
	
p=(h+l-7*m+114)%31;
easter_Date=p+1;     //(date in Easter Month)
if (easter_Month==3){
		 
	printf("Enter year: Easter is March %d in %d. \n",  easter_Date, year);
	}
else {
	printf("Enter year: Easter is April %d in %d. \n", easter_Date, year);
	}
return 0;
}
