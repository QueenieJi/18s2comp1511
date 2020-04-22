// Assignment 1 Mandelbrot: Pixel coloring functions
// pixelColor.c
//
// Completed by
// Queenie (z5191512)
//
// Modified on 2018-08-28
// Tutor's name (dayHH-lab)
//
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include "mandelbrot.h"
#include "pixelColor.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
struct pixel pixelColor(int steps) {
    struct pixel color = {
        .red = steps,
        .green = steps,
        .blue = steps,
    };
	//Changing color by using different functions in different range.
	if (steps >= 15 && steps <= MAX_STEPS) {
		color.red = 133 + 100 * fabs(cos(steps));
		color.green = 133 + 100* fabs(sin(steps));
		color.blue = 150 + 100* fabs(cos(steps));
	}else if(steps < 15 && steps >= 0) {
		color.red = 233 * fabs(cos(steps)* cos(steps));
		color.green = 233;
		color.blue = 150 * fabs(sin(steps) * sin(steps));
	}
	else {
		color.red = 255;
		color.green = 127;
		color.blue = 80;
	}

    
	// TODO: Change the color of the pixel for different numbers of
    // steps.

    return color;
}
