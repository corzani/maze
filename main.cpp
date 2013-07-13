/*
 *
 * File:   main.cpp
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */

#include <iostream>

#include "MazePng.h"

using namespace std;

int main(int argc, char *argv[]) {
	unsigned int w, h;
	if (argc == 3) {
		w = atoi(argv[1]);
		h = atoi(argv[2]);
	} else {
		w = 3;
		h = 3;
	}

	std::cout << "MaZe " << w << "x" << h << std::endl;
	MazePng m(w, h);

	m.generate(0);
	m.setPassages(0,0);
	m.toPng(10);
	return 0;
}
