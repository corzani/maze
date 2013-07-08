/*
 *
 * File:   main.cpp
 * Author: Cesare Jacopo Corzani
 *
 * Created on June 28, 2013, 2:31 AM
 *
 */

#include <iostream>
#include "MazeDebug.h"

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

	MazeDebug m(w, h);

	m.generate(0);
	cout << m.toString();

	return 0;
}
