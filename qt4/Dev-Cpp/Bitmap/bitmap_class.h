#ifndef	BITMAP_CLASS_H
#define	BITMAP_CLASS_H

/* 
	Okay here's our class for holding the information read in from the 8-bit .bmp file
	As you are well aware, when we load an image (any image) we need a place to store
	it, so as WE know how it is laid out.  I'm going to use a DIBSection to store the 
	8-bit .bmp

	There are basically two types of bitmaps.  Device Dependent Bitmaps (dependent on the
	video card) and Device Independent Bitmaps (does not depend on video card, but slower
	to work	with).  However, a DIBSection gives you the benefits of both (doesn't depend 
	on video card, fast, access to pixel bits)

	I'd say if your working in Win32, use a DIBSection to store all of your images once
	you have loaded them is a safe, effective way to go.

	Now the only function that is going to be HEAVILY COMMENTED (tutorialized to the max)
	is the loadBMP() method in our class.  This is what this tutorial focuses on.  If you
	want, you can easily cut-n-paste this code in a different program and load an 8-bit
	bitmap into an text file or whatever :)

	On with the show......
   
*/

#include <windows.h>
#include <stdio.h>

// By doing this we save ourselves some typing (yeah)
typedef unsigned char uchar;
typedef unsigned int uint;

// This what will hold our 8-bit .bmp we load in
// This DIB_BITMAP only supports 8-bit .bmp files
// loadBMP() will have HEAVY ERROR checking, the rest of the functions will have LITTLE error checking
class DIB_BITMAP
{
	public:

		// Constructor() -- Zero's out DIB_BITMAP
		DIB_BITMAP():hbitmap(NULL),old_bmp(NULL),bmp_hdc(NULL),surface_bits(NULL),
					 bmp_width(0),bmp_height(0),bmp_stride(0)
					 { GdiFlush(); /* Guarentee that writing to DIB_BITMAP is okay */ }

		// Data Access Functions ************
		
			inline int get_width() const { return bmp_width; } 
			inline int get_height() const { return bmp_height; }
			inline int get_stride() const { return bmp_stride; }
			inline HDC get_bmpHDC() const { return bmp_hdc; }

		
		// ****** End of Data Access Functions

		// Returns true for success -- false otherwise
		// If set_size is called on a DIB_BITMAP that already has memory associated with it
		// that memory is freed and the new size is implemented
		bool set_size(HDC hdc, int width, int height);

		// If we're dealing with an 8-bit DIB_BITMAP, this function will set the 
		// palette to what is passed in
		// Returns true for success -- false otherwise
		bool set_palette(int start_color, int num_colors, RGBQUAD *colors);

		bool loadBMP(char *file_name, HDC hdc); // This is where all the magic happens :)
											   // This will load an 8-bit .bmp file
											  // If successful the return value is true
											 // otherwise it's false

		uchar* getLinePtr(int which_line); // returns a pointer to the line passed in
		
		// Deconstructor();
		~DIB_BITMAP();
		

	private:

		int bmp_width;
		int bmp_height;
		int bmp_stride;
		
		HBITMAP hbitmap;  
		HBITMAP old_bmp;

		HDC bmp_hdc;

		uchar *surface_bits; // Pointer to the pixels

		void freeDIB_BMP(); // Frees all mem associated with DIB_BITMAP
		
};

#endif
