/*
 *
 * File:   MazeDebug.cpp
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */
#include "MazeDebug.h"

MazeDebug::MazeDebug(const unsigned int width, const unsigned int height) :
		AbstractMaze(width, height) {

}

MazeDebug::~MazeDebug() {

}

void MazeDebug::debugMazeStp() {
printBinary();
}


std::string MazeDebug::toString() {
	std::string out("+");
	std::string temp;

	for (unsigned int i = 0; i < width; ++i) {
		out += "-+";
	}
	out += "\n";

	for (unsigned int i = 0; i < height; ++i) {
		out += "|";
		temp = "+";

		for (unsigned int j = 0; j < width; ++j) {
			switch ((cells[(i * width) + j] & 0x0C) >> 2) {

			case 3:
				out += " |";
				temp += "-+";
				break;
			case 2:
				out += "  ";
				temp += "-+";
				break;
			case 1:
				out += " |";
				temp += " +";
				break;
			case 0:
				out += "  ";
				temp += " +";
				break;

			}
		}
		out += "\n" + temp + "\n";

	}

	return out;
}

std::string MazeDebug::printBinary() {

	std::string out = "";
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {

			for (int w = 7; w >= 0; --w) {
				if (cells[(i * width) + j] & ((short) pow(2, w))) {
					std::cout << "1";
				} else {
					std::cout << "0";
				}
			}

			std::cout << " ";
		}
		std::cout << std::endl;

	}
	return out;
}


void MazeDebug::cellStatus(unsigned int cellId) {

	using namespace std;

	short cell = cells[cellId];

	cout << "Analysis " << cellId << endl << "\t";

	if ((cell & 0x80) >> 7) {
		cout << "Down ";
	}
	if ((cell & 0x40) >> 6) {
		cout << "DX ";
	}
	if ((cell & 0x20) >> 5) {
		cout << "Up ";
	}
	if ((cell & 0x10) >> 4) {
		cout << "Sx ";
	}
	if ((cell & 0xF0) == 0) {
		cout << "No cells available" << endl;
	} else {
		cout << "cell(s) available" << endl;
	}
	cout << "\t";
	if ((cell & 0x08) >> 3) {
		cout << "Down ";
	}
	if ((cell & 0x04) >> 2) {
		cout << "Dx ";
	}
	if ((cell & 0x02) >> 1) {
		cout << "Up ";
	}
	if (cell & 0x01) {
		cout << "Sx ";
	}
	if ((cell & 0x0F) == 0) {
		cout << "No walls ?!?!?" << endl;
	} else {
		cout << "wall(s) available" << endl;
	}

}