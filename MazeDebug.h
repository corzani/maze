/*
 *
 * File:   MazeDebug.h
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */
#ifndef MAZEDEBUG_H_
#define MAZEDEBUG_H_
#include "Maze.h"
#define DEBUG

class MazeDebug: public AbstractMaze {
public:
	MazeDebug(const unsigned int width, const unsigned int height);
	virtual ~MazeDebug();
	std::string toString();
	std::string printBinary();
	void cellStatus(unsigned int cellId);
	void show();


private:
	void debugMazeStp();
	void printTopBorder();
	inline void printRow(unsigned int index);
	void printBody();

};

#endif /* MAZEDEBUG_H_ */
