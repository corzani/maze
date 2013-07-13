/*
 * MazePng.h
 *
 *  Created on: 12 Jul 2013
 *      Author: yac
 */

#ifndef MAZEPNG_H_
#define MAZEPNG_H_
#include "Maze.h"
#include <png.h>

class MazePng: public AbstractMaze {
public:
	MazePng(const unsigned int width, const unsigned int height);
	virtual ~MazePng();
	void toPng(unsigned int scale);
private:
	void createImage(png_bytep *row_pointers, unsigned int scale);

};

#endif /* MAZEPNG_H_ */
