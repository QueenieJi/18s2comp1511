// Find and return the minimum positive value
// from the values in a given array.
// By ... (z0000000)
// Written on 2018-0?-??
// Tutor (dayHH-lab)


// You need to implement this function

// Returns the minimum positive value from a given array.
// A value is a positive value if it is greater than zero.
// If there are no positive values in a given list,
// the function should return zero.

int arrayPositiveMin(int a[], int size) {
 	int i = 0;
	int pmin = 0;
	if (a[0] > 0) {
		pmin = a[0];
	} else {
		pmin = 0;
	}
	while ( i < size) {
		if (a[i] >= 0 && pmin == 0 ) {
			pmin = a[i];
		}
		if (a[i] < pmin && a[i] > 0) {
			pmin = a[i];
		}
		i++;	

	}
    // Implement this function 
    // You also need to change the return value.
    
    return pmin;

}
