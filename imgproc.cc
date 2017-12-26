
// an image processing program (imgproc.cc) that uses your image toolkit.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "imgtools.h"

int main( int argc, char *argv[])
{
	// If the user fails to provide an argument.
	if (argc < 3) {
		fprintf(stderr, "Error: no argument provided.\n");
		return 1;
	}
	
	// Extract the name of the text file and verify it exists.
	char *filename;
	filename = argv[2];
	
	// Open the infile.
	FILE *infile;
	infile = fopen(filename, "r");
	
	// Check whether the file exists.
	if (infile == 0) {
		fprintf(stderr, "Error: the file does not exist.\n");
		return 1;
	}
	
	// Load the image
	Image *image;	
	Image picture = loadImage(infile);
	image = &picture;
	
	// Manipulating and filtering digital images.
	
	// Filters the image by converting it to grayscale.
	if (strcmp(argv[1], "-g") == 0) {
		toGrayScale(image, image->height, image->width);
	}
	
	// Horizontal flip
	else if (strcmp(argv[1], "-h") == 0) {
		int horizontal = 1;
		flipImage(image, horizontal, image->height, image->width);
	}
	
	// Vertical flip
	else if (strcmp(argv[1], "-v") == 0) {
		int horizontal = 0;
		flipImage(image, horizontal, image->height, image->width);
	}
	
	// Enlarging the image to be twice its original size.
	else if (strcmp(argv[1], "-e") == 0) 
		enlargeImage(image, image->height, image->width);
	
	// Shrinking the size of the image by half.
	else 
		shrinkImage(image, image->height, image->width);
	
	// Saves an image to a text file as a “P3” PPM formatted image.
	saveImage(image);
	
	// Close the infile after reading.
	fclose(infile);
}

