/*
 *
 * File:   Maze.h
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */


#ifndef MAZE_H_
#define MAZE_H_

#include <string>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <map>
#include "math.h"

class AbstractMaze {
public:
	AbstractMaze(const unsigned int width, const unsigned int height);
	//  Maze(const Maze& orig);
	virtual ~AbstractMaze();
	//void generate();
	void generate(int start);
	enum directions {
		MOV_NO, MOV_LEFT, MOV_UP, MOV_RIGHT, MOV_DOWN
	};
	void setPassages(const unsigned int start,const unsigned int exit);

protected:
	unsigned int size;
	unsigned int width;
	unsigned int start;
	unsigned int exit;
	unsigned int height;
	short *cells;
	inline void setVisited(unsigned int cellId);
	void knockWall(unsigned int startCellId, unsigned int endCellId,
			AbstractMaze::directions direction);
	AbstractMaze::directions getNext(unsigned int cellId, short *cells,
			unsigned int *resultId);
	const static short map[];
	void compactMemory();

};

class Maze: public AbstractMaze{
public:
	Maze(const unsigned int width, const unsigned int height);
	virtual ~Maze();
	std::string toString();
	std::string printBinary();
private:
	void debugMazeStp();
};

#endif /* MAZE_H_ */
