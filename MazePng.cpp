/*
 * MazePng.cpp
 *
 *  Created on: 12 Jul 2013
 *      Author: yac
 */

#include "MazePng.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const png_byte WALL = 0x00;
const png_byte PATH = 0xFF;

MazePng::MazePng(const unsigned int width, const unsigned int height) :
		AbstractMaze(width, height) {

}

MazePng::~MazePng() {
}

void MazePng::toPng(unsigned int scale) {

	/* PNG structs and types */
	png_byte color_type;
	png_byte bit_depth;
	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_pointers;

	int height, width;
	FILE *fp;

	width = (this->width * 2) + 1;
	height = (this->height * 2) + 1;

	color_type = PNG_COLOR_TYPE_RGB;
	bit_depth = 8; /* Number of bits per color, not per pixel */

	/* Dynamic 2D array in C */
//   row_pointers = (png_bytep *)malloc( sizeof(png_bytep) * height);
	row_pointers = new png_bytep[height];

	for (int i = 0; i < height; ++i) {
		row_pointers[i] = new png_byte[width * 3];
		for (int j = 0; j < width * 3; j += 3) {
			row_pointers[i][j] = WALL;
			row_pointers[i][j + 1] = WALL;
			row_pointers[i][j + 2] = WALL;
		}
	}

	createImage(row_pointers, 0);

	/* Write the data out to the PNG file */
	fp = fopen("out.png", "wb");
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
			PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, NULL);

	for (int i = 0; i < height; ++i) {
		delete row_pointers[i];
	}

	delete[] row_pointers;

}

void inline setPixel(png_bytep *row_pointers, unsigned int x, unsigned int y,
		png_byte type) {
	row_pointers[y][0 + 3 * x] = type;
	row_pointers[y][1 + 3 * x] = type;
	row_pointers[y][2 + 3 * x] = type;

}

void MazePng::createImage(png_bytep *row_pointers, unsigned int scale) {

	/*
	 for (unsigned int x = 0; x < ((width * 2) + 1); ++x) {
	 setPixel(row_pointers, x, 0, WALL);
	 }
	 */

	if (start < width) {
		setPixel(row_pointers, start * 2 + 1, 0, PATH);
	}

	png_byte temp[2] = { 0 };

	for (unsigned int y = 0; y < height; ++y) {
		setPixel(row_pointers, 0, (y * 2) + 1, WALL);

		for (unsigned int x = 0; x < width; ++x) {

			switch ((cells[(y * width) + x] & 0xC0) >> 6) {
			/*
			 case 3:
			 temp[0] = WALL;
			 temp[1] = WALL;
			 break;
			 */
			case 2:
				temp[0] = PATH;
				setPixel(row_pointers, 2 + (x * 2), (y * 2) + 1, temp[0]);
				break;
			case 1:
				temp[1] = PATH;
				setPixel(row_pointers, 1 + (x * 2), (y * 2) + 2, temp[1]);
				break;
			case 0:
				setPixel(row_pointers, 2 + (x * 2), (y * 2) + 1, temp[0]);
				setPixel(row_pointers, 1 + (x * 2), (y * 2) + 2, temp[1]);
				break;

			}
			setPixel(row_pointers, 1 + (x * 2), (y * 2) + 1, PATH);
		}

	}

}
