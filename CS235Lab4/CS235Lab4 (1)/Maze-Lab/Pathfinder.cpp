#include "Pathfinder.h"
	                                         
	string Pathfinder::toString() const
	{
	    stringstream ss;
        
        for(int h = 0; h < HI_SIZE; h++){
            for(int r = 0; r < ROW_SIZE; r++){
                for(int c = 0; c < COL_SIZE; c++){
                    ss << maze_grid[h][r][c];
										if(c != 4)
										ss << " ";
                }
                ss << endl;
            }
						if(h !=4)
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
        for(int h = 0; h < 5; h++){
            for(int r = 0; r < 5; r++){
                for(int c = 0; c < 5; c++){
                    randMaze[h][r][c] = rand() % 2;
										if(randMaze[h][r][c] == 1)
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
			for (int h = 0; h < HI_SIZE; h++){

				for (int r = 0; r < ROW_SIZE; r++){
					getline(file, line);
					stringstream ss(line);
					for (int c =0; c < COL_SIZE; c++){
						int value;
						ss >> value;
						maze_grid[h][r][c] = value;
					}
				}
				getline(file, line);
			}
		}
	    return(true);
	}
	
	
	bool Pathfinder::find_maze_path(int grid[HI_SIZE][ROW_SIZE][COL_SIZE], int h, int r, int c) {
	  // cout << "find_maze_path ["<<r<<"]["<<c<<"]"<<"["<<h<<"]" <<endl;
	  // cout << this->toString();
	  if (r < 0 || c < 0 || h < 0 || r >= ROW_SIZE || c >= COL_SIZE || h >= HI_SIZE)
	    return false;      // Cell is out of bounds.
	  else if (grid[h][r][c] != BACKGROUND)
	    return false;      // Cell is on barrier or dead end.
	  else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && h == HI_SIZE - 1) {
	    grid[h][r][c] = PATH;         // Cell is on path
	    solution.insert(solution.begin() + 0, "("+to_string(c)+", "+to_string(r)+", "+to_string(h)+")");
	    return true;               // and is maze exit.
	  }
	  else { 
	    grid[h][r][c] = PATH;
			// solution.push_back("("+to_string(r)+", "+to_string(c)+", "+to_string(h)+")");
	    if (find_maze_path(grid, h , r - 1, c) //down
	        || find_maze_path(grid, h, r + 1, c) //up
	        || find_maze_path(grid, h, r , c - 1) //left
	        || find_maze_path(grid, h, r, c + 1)
					|| find_maze_path(grid, h - 1, r, c)
					|| find_maze_path(grid, h + 1, r, c) ) { 
	      solution.insert(solution.begin() + 0, "("+to_string(c)+", "+to_string(r)+", "+to_string(h)+")");
	      return true;
	    }
	    else {
	      grid[h][r][c] = TEMPORARY;  // Dead end.
	      return false;
	    }
	  }
	}
	 
	vector<string> Pathfinder::solveMaze()
	{
		solution.clear();
		int mazeToSolve[ROW_SIZE][COL_SIZE][HI_SIZE];
		for (int h = 0; h < HI_SIZE; h++){
			for (int r = 0; r < ROW_SIZE; r++){
				for (int c = 0; c < COL_SIZE; c++){
					mazeToSolve[h][r][c] = maze_grid[h][r][c];
				}
			}
		}
		
		find_maze_path(mazeToSolve, 0,0,0);

		for(auto s:solution) {
			cout <<s<<endl;
		}
		
		// if(solution.size() > 0){
		// 	// reverse(solution.begin(), solution.end());
		// 	cout << solutionTemp.at(0) << "solution *************";
		// }
	    return solution;
	}
