// This is a backtracking approach (recusrion) to solve a Sudoku board

#include <iostream>

// Function to print the Sudoku grid
void printGrid(int grid[9][9]) {

	for(int row = 0; row < 9; row++) {
		
		if(row % 3 == 0) {
				std::cout << " -----------------------------" << std::endl;
		}

		for(int col = 0; col < 9; col++) {

			if(col % 3 == 0) {
				std::cout << "|";
			}

			if(grid[row][col] == 0) {
				std::cout << " . ";
			} else {
				std::cout << " " << grid[row][col] << " ";
			}
		}

		std::cout << "|" << std::endl;

	}
	std::cout << " -----------------------------" << std::endl;
}

// Check if a given number can be placed in an empty cell without breaking any of three rules
bool checkPlacement(int board[9][9], int value, int row, int col) {

	// Row check
	for(int tmp=0; tmp<9; tmp++) {
		if(value == board[row][tmp]) {
			return false;
		}
	}

	// Column check
	for(int tmp=0; tmp<9; tmp++) {
		if(value == board[tmp][col]) {
			return false;
		}
	}

	// 3x3 sub-grid check
	for(int s_row = row - row%3; s_row <= row - row%3 + 2; s_row++) {
		for(int s_col = col - col%3; s_col <= col - col%3 + 2; s_col++) {
			if(value == board[s_row][s_col]) {
				return false;
			}
		}
	}

	return true;
}

bool solver(int board[9][9], int row, int col) {

	// Reached end of row, procede to next row
	if(col == 9) {
		col = 0;
		row++;

		// Reached the final cell, the board must be filled
		if(row==9) {
			return true;
		}
	}
	
	// If cell is not empty check next cell
	if(board[row][col] != 0) {
		return solver(board, row, col+1);
	}

	// Check through 1-9 if can be placed in the empty cell
	for(int i = 1; i <= 9; i++) {
		if(checkPlacement(board, i, row, col)) {
			board[row][col] = i;
			//printGrid(board);
			if(solver(board, row, col+1)) {
				return true;
			}
			board[row][col] = 0; // If is not possible to place 1-9: backtrack
		}
	}

	return false; // The board has not solution
}


int main() {
	// Sudoku problem exemple
	int grid[9][9] = {{0, 0, 0, 3, 0, 9, 0, 0, 7},  
	                  {0, 6, 4, 5, 0, 0, 0, 0, 0},  
	                  {3, 0, 0, 0, 2, 0, 0, 9, 0},  
	                  {0, 0, 6, 0, 0, 0, 0, 0, 9},  
	                  {2, 0, 0, 0, 0, 6, 0, 0, 0},  
	                  {0, 0, 0, 0, 7, 0, 0, 4, 0},  
	                  {1, 5, 0, 0, 0, 0, 6, 0, 0},  
	                  {0, 0, 0, 0, 1, 0, 0, 8, 0},  
	                  {0, 0, 0, 0, 0, 2, 7, 0, 5}};              


	// Print board before solving
	printGrid(grid);
	bool solvable = solver(grid, 0, 0);
	if(solvable) {
		std::cout << "Solution was found :)" << std::endl;
		printGrid(grid); // Print board after finding solution
	} else {
		std::cout << "Solution was not found :(" << std::endl;
	}

	
	return 0;
}