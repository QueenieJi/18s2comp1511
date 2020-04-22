// Alex Linker 2017-08-13
// This program prints out facts about a circle given its radius,
// using functions.

#include <stdio.h>
#include <math.h>

double area(double radius);
double circumference(double radius);
double diameter(double radius);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    double radius;

    printf("Enter circle radius: ");
    scanf("%lf", &radius);

    printf("Area          = %lf\n", area(radius));
    printf("Circumference = %lf\n", circumference(radius));
    printf("Diameter      = %lf\n", diameter(radius));

    return 0;
}


// Calculate the area of a circle, given its radius.
double area(double radius) {
    double a = radius * radius * M_PI; 
	return a;
}

// Calculate the circumference of a circle, given its radius.
double circumference(double radius) {
	double c = 2 * radius * M_PI;
    return c;
}

// Calculate the diameter of a circle, given its radius.
double diameter(double radius) {
	double d = 2 * radius;
    return d;
}
