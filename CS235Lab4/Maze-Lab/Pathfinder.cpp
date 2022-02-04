#include "Pathfinder.h"
	                                         
	string Pathfinder::toString() const
	{
	    stringstream ss;
        
        for(int r = 0; r < ROW_SIZE; r++){
            for(int c = 0; c < COL_SIZE; c++){
                for(int h = 0; h < HI_SIZE; h++){
                    ss << maze_grid[r][c][h];
										if(h != 4)
										ss << " ";
                }
                ss << endl;
            }
						if(r !=4)
            ss << endl;
        }
		return ss.str();
	}

	void Pathfinder::createRandomMaze()
	{
				int ones = 0;
				int zeroes = 0;
				int randMaze[5][5][5];
				do
        for(int r = 0; r < 5; r++){
            for(int c = 0; c < 5; c++){
                for(int h = 0; h < 5; h++){
                    randMaze[r][c][h] = rand() % 2;
										if(randMaze[r][c][h] == 1)
										ones++;
										else
										zeroes++;
								}
            }
        }
				while((ones - zeroes) < 10);
        randMaze[0][0][0] = 1;
        randMaze[4][4][4] = 1;
	}

	//-----------------------------------------------------------------------------------------

	//Part 2-----------------------------------------------------------------------------------
	/*
	* importMaze
	*
	* Reads in a maze from a file with the given file name and stores it as the current maze.
	* Does nothing if the file does not exist or if the file's data does not represent a valid
	* maze.
	*
	* The file's contents must be of the format described above to be considered valid.
	*
	* Parameter:	file_name
	*				The name of the file containing a maze
	* Returns:		bool
	*				True if the maze is imported correctly; false otherwise
	*/
	bool Pathfinder::importMaze(string file_name)
	{
		string line;
		cout << "importMaze from "<<file_name<<endl;
		ifstream check (file_name.c_str());
		vector<string> testMaze;
		vector<char> testMazeInt;
		int iterations = 0;
		while(getline(check, line)){
			iterations++;
			testMaze.push_back(line);
		}

		if(iterations != 29){
			return false;
		}
		
		for (int i = 0; i < testMaze.size(); i++){
			string line = testMaze.at(i);
			for(int j = 0; j < line.size(); j++){
				if(line.at(j) == '0' || line.at(j) == '1' || line.at(j) == ' '){
				testMazeInt.push_back(line.at(j));
				}
				else {return false;}
			}
		}
		
		if(testMazeInt.at(224) != '1' || testMazeInt.at(224) != '1')
			return false;
		check.close();
		ifstream file (file_name.c_str());
		if (file.is_open()) {
			string line;
			cout << endl;
			for (int r = 0; r < HI_SIZE; r++){

				for (int c = 0; c < ROW_SIZE; c++){
					getline(file, line);
					stringstream ss(line);
					for (int h =0; h < COL_SIZE; h++){
						int value;
						ss >> value;
						maze_grid[r][c][h] = value;
					}
				}
				getline(file, line);
			}
		}
	    return(true);
	}
	
	
	bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][HI_SIZE], int r, int c, int h) {
	  cout << "find_maze_path ["<<r<<"]["<<c<<"]"<<"["<<h<<"]" <<endl;
	  // cout << this->toString();
	  if (r < 0 || c < 0 || h < 0 || r >= ROW_SIZE || c >= COL_SIZE || h >= HI_SIZE)
	    return false;      // Cell is out of bounds.
	  else if (grid[r][c][h] != BACKGROUND)
	    return false;      // Cell is on barrier or dead end.
	  else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && h == HI_SIZE - 1) {
	    grid[r][c][h] = PATH;         // Cell is on path
	    solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(h)+")");
	    return true;               // and is maze exit.
	  }
	  else { 
	    // Recursive case.
	    // Attempt to find a path from each neighbor.
	    // Tentatively mark cell as on path.
	    grid[r][c][h] = PATH;
			solution.push_back("("+to_string(r)+","+to_string(c)+","+to_string(h)+")");
	    if (find_maze_path(grid, r - 1, c, h) //down
	        || find_maze_path(grid, r + 1, c, h) //up
	        || find_maze_path(grid, r, c - 1, h) //left
	        || find_maze_path(grid, r, c + 1, h )
					|| find_maze_path(grid, r, c, h - 1)
					|| find_maze_path(grid, r, c, h + 1) ) { 
	      
	      return true;
	    }
	    else {
	      grid[r][c][h] = TEMPORARY;  // Dead end.
	      return false;
	    }
	  }
	}
	  //Part 3-----------------------------------------------------------------------------------
	/*
	* solveMaze
	*
	* Attempts to solve the current maze and returns a solution if one is found.
	*
	* A solution to a maze is a list of coordinates for the path from the entrance to the exit
	* (or an empty vector if no solution is found). This list cannot contain duplicates, and
	* any two consecutive coordinates in the list can only differ by 1 for only one
	* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
	* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
	* where x, y, and z are the integer coordinates of a cell.
	*
	* Understand that most mazes will contain multiple solutions
	*
	* Returns:		vector<string>
	*				A solution to the current maze, or an empty vector if none exists
	*/
	
	vector<string> Pathfinder::solveMaze()
	{
		int mazeToSolve[ROW_SIZE][COL_SIZE][HI_SIZE];
		for (int r = 0; r < HI_SIZE; r++){
			for (int c = 0; c < ROW_SIZE; c++){
				for (int h = 0; h < COL_SIZE; h++){
					mazeToSolve[r][c][h] = maze_grid[r][c][h];
				}
			}
		}
		find_maze_path(mazeToSolve, 0,0,0);
		for(auto s:solution) {
			cout <<s<<endl;
		}
	    return solution;
	}
