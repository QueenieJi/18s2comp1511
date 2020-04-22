// Find the average of the values in a given array.
// By ... (z0000000)
// Written on 2018-0?-??
// Tutor (dayHH-lab)

// You need to implement this function

// Calculates the average of all the values in a given array,
// and returns the average value.
double arrayAverage(int a[], int size) {
	int i = 0;
	float sum = 0;

	while ( i < size) {
		sum = sum + a[i];
		i++;
	}
	
	float average = sum / size;
    // implement this function and 
    // change return value

    return average;

}
