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
	cells = new short[width * height];

	this->width = width;
	this->height = height;
	this->size = width * height;

	for (unsigned int i = 1; i < width - 1; ++i) {
		cells[i] = 0xDF;
	}

	int lastRow = width * (height - 1);

	for (unsigned int i = 1; i < height - 1; ++i) {
		cells[i * width] = 0xEF;
		cells[(i * width) + width - 1] = 0xBF;
		for (unsigned int j = 1; j < width - 1; ++j) {
			cells[(i * width) + j] = 0xFF;
		}
	}

	for (unsigned int i = 1; i < width - 1; ++i) {
		cells[lastRow + i] = 0x7F;
	}

	cells[0] = 0xCF;
	cells[width - 1] = 0x9F;
	cells[lastRow] = 0x6F;
	cells[(width * height) - 1] = 0x3F;

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

AbstractMaze::directions AbstractMaze::getNext(unsigned int cell, short *cells,
		unsigned int *result) {
	short cellBoundaries = (cells[cell] & 0xF0) >> 4;
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

inline void AbstractMaze::setVisited(unsigned int cellId) {
// Bx CELL
	if (cellId + width < size) {
		cells[cellId + width] &= 0xDF;
	}
// Rx CELL
	if (cellId + 1 < size) {
		cells[cellId + 1] &= 0xEF;
	}
// Tx CELL
	if (cellId + 1 > width) {
		cells[cellId - width] &= 0x7F;

	}
// Lx CELL
	if (cellId > 0) {
		cells[cellId - 1] &= 0xBF;
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

void Maze::debugMazeStp() {
}

std::string Maze::toString() {
	return "";
}

std::string Maze::printBinary() {
	return "";
}
