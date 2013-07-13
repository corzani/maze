/*
 *
 * File:   Maze.cpp
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */

#include "Maze.h"

/*
 *
 * C D 9
 * E F B
 * 6 7 3
 *
 *
 */

const short AbstractMaze::map[] = { MOV_NO, MOV_NO, MOV_NO, MOV_NO, MOV_NO,
		MOV_NO, MOV_LEFT, MOV_LEFT, MOV_LEFT, MOV_LEFT, MOV_LEFT, MOV_LEFT,
		MOV_UP, MOV_UP, MOV_UP, MOV_UP, MOV_UP, MOV_UP, MOV_LEFT, MOV_UP,
		MOV_LEFT, MOV_UP, MOV_LEFT, MOV_UP, MOV_RIGHT, MOV_RIGHT, MOV_RIGHT,
		MOV_RIGHT, MOV_RIGHT, MOV_RIGHT, MOV_LEFT, MOV_RIGHT, MOV_LEFT,
		MOV_RIGHT, MOV_LEFT, MOV_RIGHT, MOV_UP, MOV_RIGHT, MOV_UP, MOV_RIGHT,
		MOV_UP, MOV_RIGHT, MOV_LEFT, MOV_UP, MOV_RIGHT, MOV_LEFT, MOV_UP,
		MOV_RIGHT, MOV_DOWN, MOV_DOWN, MOV_DOWN, MOV_DOWN, MOV_DOWN, MOV_DOWN,
		MOV_LEFT, MOV_DOWN, MOV_LEFT, MOV_DOWN, MOV_LEFT, MOV_DOWN, MOV_UP,
		MOV_DOWN, MOV_UP, MOV_DOWN, MOV_UP, MOV_DOWN, MOV_LEFT, MOV_UP,
		MOV_DOWN, MOV_LEFT, MOV_UP, MOV_DOWN, MOV_RIGHT, MOV_DOWN, MOV_RIGHT,
		MOV_DOWN, MOV_RIGHT, MOV_DOWN, MOV_LEFT, MOV_RIGHT, MOV_DOWN, MOV_LEFT,
		MOV_RIGHT, MOV_DOWN, MOV_UP, MOV_RIGHT, MOV_DOWN, MOV_UP, MOV_RIGHT,
		MOV_DOWN };

AbstractMaze::AbstractMaze(const unsigned int width,
		const unsigned int height) {
	std::srand(time(NULL));

	this->width = width;
	this->height = height;

	size = width * height;
	cells = new short[size];

	start = size;
	exit = size;

	for (unsigned int i = 1; i < width - 1; ++i) {
		cells[i] = 0xFD;
	}

	int lastRow = width * (height - 1);

	for (unsigned int i = 1; i < height - 1; ++i) {
		cells[i * width] = 0xFE;
		cells[(i * width) + width - 1] = 0xFB;
		for (unsigned int j = 1; j < width - 1; ++j) {
			cells[(i * width) + j] = 0xFF;
		}
	}

	for (unsigned int i = 1; i < width - 1; ++i) {
		cells[lastRow + i] = 0xF7;
	}

	cells[0] = 0xFC;
	cells[width - 1] = 0xF9;
	cells[lastRow] = 0xF6;
	cells[(width * height) - 1] = 0xF3;

}
//DONE
void AbstractMaze::setPassages(const unsigned int start,
		const unsigned int exit) {

	if (this->start < width) {
		cells[this->start] |= 0x20;
	} else if (this->start < width + height) {
		cells[((this->start - width) * width)] |= 0x10;
	}

	if (this->exit < width) {
		cells[width * (height - 1) + this->exit] |= 0x80;
	} else if (this->exit < width + height) {
		cells[(this->exit - width) * width + (width - 1)] |= 0x40;
	}

	this->start = start;
	this->exit = exit;

	if (start < width) {
		cells[start] &= 0xDF;
	} else if (start < width + height) {
		cells[((start - width) * width)] &= 0xEF;
	}

	if (exit < width) {
		cells[width * (height - 1) + exit] &= 0x7F;
	} else if (exit < width + height) {
		cells[(exit - width) * width + (width - 1)] &= 0xBF;
	}

}

void AbstractMaze::generate(int start) {

	using namespace std;

	unsigned int totalCells = width * height;
	unsigned int currentCell = start;
	unsigned int tempCell = 0;
	unsigned int visitCount = 1;

	std::stack<unsigned int> s;
	AbstractMaze::directions direction;

	s.push(start);
	setVisited(start);

	while (visitCount < totalCells) {

		direction = getNext(currentCell, cells, &tempCell);

		if (direction > 0) {

			knockWall(currentCell, tempCell, direction);
			s.push(currentCell);
			currentCell = tempCell;
			++visitCount;

		} else {
			currentCell = s.top();
			s.pop();
		}
	}

}


//DONE
AbstractMaze::directions AbstractMaze::getNext(unsigned int cell, short *cells,
		unsigned int *result) {
	short cellBoundaries = (cells[cell] & 0x0F);
	short tmp;
	if (cellBoundaries == 0x0F) {
		tmp = (std::rand() % 4) + 1;
	} else {
		tmp = map[(6 * cellBoundaries) + (std::rand() % 6)];

	}

//	MOV_LEFT, MOV_UP, MOV_RIGHT, MOV_DOWN
	switch (tmp) {
	case 1:
		*result = cell - 1;

		break;
	case 2:
		*result = cell - width;

		break;
	case 3:
		*result = cell + 1;
		break;
	case 4:
		*result = cell + width;
		break;
	default:
		break;
	}

	return (AbstractMaze::directions) tmp;

}

void AbstractMaze::knockWall(unsigned int startCellId, unsigned int endCellId,
		AbstractMaze::directions direction) {

	static short startPattern = 0, endPattern = 0;
	switch (direction) {
	case MOV_LEFT:
		startPattern = 0xEE;
		endPattern = 0xBB;
		break;
	case MOV_UP:
		startPattern = 0xDD;
		endPattern = 0x77;
		break;
	case MOV_RIGHT:
		startPattern = 0xBB;
		endPattern = 0xEE;
		break;
	case MOV_DOWN:
		startPattern = 0x77;
		endPattern = 0xDD;
		break;
	case MOV_NO:
		break;
	}

	cells[startCellId] &= startPattern;
	cells[endCellId] &= endPattern;

	setVisited(endCellId);

}


void AbstractMaze::compactMemory(){

}



// DONE
inline void AbstractMaze::setVisited(unsigned int cellId) {
// Bx CELL
	if (cellId + width < size) {
		cells[cellId + width] &= 0xFD;
	}
// Rx CELL
	if (cellId + 1 < size) {
		cells[cellId + 1] &= 0xFE;
	}
// Tx CELL
	if (cellId + 1 > width) {
		cells[cellId - width] &= 0xF7;

	}
// Lx CELL
	if (cellId > 0) {
		cells[cellId - 1] &= 0xFB;
	}
}

AbstractMaze::~AbstractMaze() {
	delete[] cells;
}

Maze::~Maze() {
}

Maze::Maze(const unsigned int width, const unsigned int height) :
		AbstractMaze(width, height) {
}

