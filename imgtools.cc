#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "imgtools.h"

// Loads a PPM formatted image from file.
// The image should be returned within the appropriate structure.
Image loadImage(FILE *infile)
{
	
	char magicNum[4];
	int row, col;
	int maxRGB;	
	
	// Get magic number, height, and width of the image
	fgets(magicNum, 4, infile);
	fscanf(infile, "%d", &col);
	fscanf(infile, "%d", &row);	
	
	// Get the maximum RGB
	fscanf(infile, "%d", &maxRGB);
	
	// Create the struct to hold the image. 
	Image image;
	image.width = col;
	image.height = row;
	
	// Create the 2D array to store the image.
	Pixel ** pixels = new Pixel *[row];
	for (int k=0; k < row; k++) {	
		pixels[k] = new Pixel [col];
	}
	
	// Get the pixels for the image.	
	for (int i=0; i < row; i++) {	
		for (int j=0; j < col; j++) {
			Pixel pixel;
			fscanf(infile, "%d", &pixel.red);
			fscanf(infile, "%d", &pixel.green);
			fscanf(infile, "%d", &pixel.blue);
			pixels[i][j] = pixel;
			
		}		
	}	
	image.pixels = pixels;
	return image;
}

// Saves an image to a text file as a “P3” PPM formatted image.
void saveImage(Image *image)
{
	
	char magicNum[] = "P3";
	int maxRGB = 255;
	
	// Open the file to save the image.
	FILE *outfile = fopen("output.ppm", "w");
	fprintf(outfile, "%s\n", magicNum);
	fprintf(outfile, "%d %d\n", image->width, image->height);
	fprintf(outfile, "%d\n", maxRGB);
	for (int i=0; i < image->height; i++) {		
		for (int j=0; j < image->width; j++) {
			fprintf(outfile, "%3d ", image->pixels[i][j].red);
			fprintf(outfile, "%3d ", image->pixels[i][j].green);
			fprintf(outfile, "%3d ", image->pixels[i][j].blue);
		}
		fprintf(outfile, "\n");
	}
	
	// Close the file.
	fclose(outfile);
}

// Filters the image by converting it to grayscale.
void toGrayScale(Image *image, int row, int col)
{
	// Convert to gray scale.
	for (int i=0; i < row; i++) {
		for (int j=0; j < col; j++) {
			int gray;
			gray = (image->pixels[i][j].red)*0.299 + 
				0.587*(image->pixels[i][j].green) + 
				0.114*(image->pixels[i][j].blue);
			image->pixels[i][j].red = gray;
			image->pixels[i][j].green = gray;
			image->pixels[i][j].blue = gray;	
		}
	}
}

// Manipulates an image by flipping it either vertically or horizontally.
void flipImage(Image *image, int horizontal, int row, int col)
{	
	// Create a new 2D array to store the new image.
	Pixel ** pixels = new Pixel *[row];
	for (int k=0; k < row; k++) {	
		pixels[k] = new Pixel [col];
	}

	// Flip vertically.
	if (horizontal == 0) {			
		for (int i=0; i < row; i++) {
			for (int j=0; j < col; j++) {
				int oldRow, oldCol;
				oldRow = row - i - 1;
				oldCol = j;
				pixels[i][j] = image->pixels[oldRow][oldCol];
			}
		}
		image->pixels = pixels;
	}
	
	// Flip horizontally.
	else { 			
		for (int i=0; i < row; i++) {
			for (int j=0; j < col; j++) {
				int oldRow, oldCol;
				oldCol = col - j - 1;
				oldRow = i;
				pixels[i][j] = image->pixels[oldRow][oldCol];
			}
		}
		image->pixels = pixels;
	}	
}

// Manipulates an image by enlarging the image to be twice its original size.
void enlargeImage(Image *image, int row, int col)
{
	image->width = col * 2;
	image->height = row * 2;
	
	// Create a new 2D array to store the new image.
	Pixel ** pixels = new Pixel *[image->height];
	for (int k=0; k < image->height; k++) {	
		pixels[k] = new Pixel [image->width];
	}
	
	for (int i=0; i < row * 2; i = i + 2) {
		for (int j=0; j < col * 2; j = j + 2) {			
			pixels[i][j] = image->pixels[i/2][j/2];			
			pixels[i][j+1] = image->pixels[i/2][j/2];			
			pixels[i+1][j] = image->pixels[i/2][j/2];			
			pixels[i+1][j+1] = image->pixels[i/2][j/2];			
		}
	}
	
	image->pixels = pixels;
	
}

// Manipulates an image by shrinking the size of the image by half.
void shrinkImage(Image *image, int row, int col)
{	
	// Reducing the size by half.
	image->width = col / 2;
	image->height = row / 2;	
	
	// Create a new 2D array to store the new image.
	Pixel ** pixels = new Pixel *[image->height];
	for (int k=0; k < image->height; k++) {	
		pixels[k] = new Pixel [image->width];
	}
	
	for (int i=0; i < row; i = i + 2) {
		for (int j=0; j < col; j = j + 2) {	
			Pixel pixel1 = image->pixels[i][j];
			Pixel pixel2 = image->pixels[i][j+1];
			Pixel pixel3 = image->pixels[i+1][j];
			Pixel pixel4 = image->pixels[i+1][j+1];
			
			// Compute the new color
			int red = (pixel1.red + pixel2.red + pixel3.red + pixel4.red) / 4;
			int green = (pixel1.green + pixel2.green + pixel3.green 
				+ pixel4.green) / 4;
			int blue = (pixel1.blue + pixel2.blue + pixel3.blue 
				+ pixel4.blue) / 4;
			
			// Create the new pixel with new color.
			Pixel newPixel;
			newPixel.red = red;
			newPixel.blue = blue;
			newPixel.green = green;			
			pixels[i/2][j/2] = newPixel;	
		}
	}
	image->pixels = pixels;	
}

















