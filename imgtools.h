
// The header file contains the function prototypes.

#ifndef _STRPROC_H
#define _STRPROC_H	

typedef unsigned char byte;
struct Pixel {
	byte red;
	byte green;
	byte blue;
};

struct Image {
	int width;
	int height;
	Pixel **pixels;
};



// Loads a PPM formatted image from file.
// The image should be returned within the appropriate structure.
Image loadImage(FILE *infile);

// Saves an image to a text file as a “P3” PPM formatted image.
void saveImage(Image *image);

// Filters the image by converting it to grayscale.
void toGrayScale(Image *image, int row, int col);

// Manipulates an image by flipping it either vertically or horizontally.
void flipImage(Image *image, int horizontal, int row, int col);

// Manipulates an image by enlarging the image to be twice its original size.
void enlargeImage(Image *image, int row, int col);

// Manipulates an image by shrinking the size of the image by half.
void shrinkImage(Image *image, int row, int col);

#endif
