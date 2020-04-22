// Find and return the minimum positive value
// from the values in a given array.
// By Queenie (z5191512)
// Written on 2018-08-14
// Tutor (dayHH-lab)


// You need to implement this function

// Returns the minimum positive value from a given array.
// A value is a positive value if it is greater than zero.
// If there are no positive values in a given list,
// the function should return zero.
#include <stdio.h>
int arrayPositiveMin(int a[], int size);

int main () {
    int size = 0;
    scanf("%d", &size);
    int a[size];
    int i = 0;
    while (i < size) {
        scanf("%d",&a[i]);
        i ++;
    }
    int positiveMin = arrayPositiveMin(a , size);
    printf("	returns %d\n", positiveMin);
    return 0;
}

int arrayPositiveMin(int a[], int size) {
    printf("arrayPositiveMin([");
    int j = 0;
    while (j < size - 1) {
        printf("%d, ", a[j]);
        j++;
    }
    int positiveMin;
    if (a[0] > 0) {
        positiveMin = a[0];
    }
    else {
        positiveMin = 0;
    }
    int count = 1;
    while ((count < size) && (count > 0)) {
       
        if ((a[count] < positiveMin) && (a[count] > 0)) {
            positiveMin = a[count];
	    
        }
        count ++;
	
    }
    printf("%d], %d) ", a[size - 1], size);
    // Implement this function 
    // You also need to change the return value.
    
    return positiveMin;

}
