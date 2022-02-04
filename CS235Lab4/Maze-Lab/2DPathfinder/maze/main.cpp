#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Pathfinder.h"

int main() {

	Pathfinder* pathptr = NULL;//the Pathfinder
	// Test 3D array
	pathptr = new Pathfinder();
	bool validMaze = pathptr->importMaze("2D.txt");
	if(!validMaze)
	return 1;
	cout << pathptr->toString();
	pathptr->solveMaze();
	exit(0);
	// End of Test 2D array

}
