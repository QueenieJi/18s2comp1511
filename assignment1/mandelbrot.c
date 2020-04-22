// Assignment 1 Mandelbrot: Mandelbrot generation functions
// mandelbrot.c
//
// Completed by
// Queenie (z5191512)
//
// Modified on 2018-08-28
// Tutor's name (dayHH-lab)
//
// Version 1.0.2: Fix minor typos in comments.
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <math.h>

// Add your own #includes here

#include "mandelbrot.h"
#include "pixelColor.h"

// Add your own #defines here

// Add your own function prototypes here


// Take a pixel grid and and the path from the web browser used to
// request the 'tile'.
//
// The requestPath will be in the form "/mandelbrot/2/{zoom}/{x}/{y}.bmp".
// In the query, 'x' and 'y' are decimals and describe the 'center' of the
// tile and need to be converted into a complex number.
// 'zoom' is an integer representing the zoom level for the tile.
void serveMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    char *requestPath
) {
    struct complex center = {0.0, 0.0};
    int z = 7;

    sscanf(
        requestPath,
        "/mandelbrot/2/%d/%lf/%lf.bmp",
        &z, &center.re, &center.im
    );

    // Use drawMandelbrot to draw the image.
    drawMandelbrot(pixels, center, z);
}

// Draw a single Mandelbrot tile, by calculating and colouring each of
// the pixels in the tile.
//
// Your function "returns" this tile by filling in the `pixels` 2D array
// that is passed in to your function.
//
// The `pixels` array is TILE_SIZE high and TILE_SIZE wide.
// The bottom left corner of the image is pixels[0][0].
//
// `center` is a complex number, representing the center of the tile.
// `z` is used to calculate the distance between each pixel in the image.
// Each pixel is 2^(-z) apart from each other.
void drawMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    struct complex center,
    int z
) {
	//Go through all the point by two loops.
	//The distance between two pixels is 2^(-z).
	//Compare the complex number tile with the central point.
	double distance = pow(2,-z);
	struct complex tile;
	int re = -TILE_SIZE / 2;
		
	while ( re < TILE_SIZE / 2) {
		int im = -TILE_SIZE / 2;
		while (im < TILE_SIZE / 2){
			tile.re = re*distance + center.re;
			tile.im = im*distance + center.im;
			int steps = escapeSteps(tile);
			pixels[im + TILE_SIZE / 2][re + TILE_SIZE / 2] = pixelColor(steps);
			//Call escapeSteps function to calculate whether the complex number
			//tile is in the brot.
			//Call pixelColor function to give the color to the brot.
			im++;
		}
		re++;
	}
		
    // TODO: COMPLETE THIS FUNCTION
}

// Determine the number of steps required to escape the Mandelbrot set,
// for the given complex number `c`.
int escapeSteps(struct complex c) {
    int steps = 0;
	struct complex w;
	w.im = 0.0;
	w.re = 0.0;
	double re_new = 0.0;
	//Add a new variable to store the previous w.re.
	double length = sqrt(w.im*w.im + w.re*w.re); 
	while (length <= 2 && steps <= MAX_STEPS) {
		w.re = w.re*w.re - w.im*w.im + c.re;
		w.im = 2 *re_new * w.im + c.im;
		re_new = w.re;
		steps++;
		length = sqrt(w.im*w.im + w.re*w.re);		
	}
	//Compare the steps with MAX_STEPS to determine whether it escapes 
	//successfully.
	if (steps == MAX_STEPS) {
		steps = NO_ESCAPE;
	}
    // TODO: COMPLETE THIS FUNCTION

    return steps;
}


// Add your own functions here.
// Remember to make them static.
