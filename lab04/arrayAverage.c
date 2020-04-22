// Find the average of the values in a given array.
// By Queenie (z5191512)
// Written on 2018-08-14
// Tutor (dayHH-lab)

// You need to implement this function

// Calculates the average of all the values in a given array,
// and returns the average value.
#include <stdio.h>
double arrayAverage(int a[], int size) {
    int i = 0;
    double sum = 0;
    printf("arrayAverage([");
  
    while (i < size - 1) {
        printf("%d, ", a[i]);
        sum = sum + a[i];
        i ++;
    }
    printf("%d], %d)",a[size - 1],size);
    sum = sum + a[size - 1];
        
    // implement this function and 
    // change return value
    double average = sum/size;
    return average;

}

int main () {
    int size;
    scanf("%d", &size);
    int a[size];
    int j;
    
    j = 0;
    while (j < size) {
        scanf("%d", &a[j]);
        j ++;
        
    }
    
    double average = arrayAverage(a , size);
    printf("returns %.1lf\n",average);
    return 0;
}


