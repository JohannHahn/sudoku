#pragma once
#include <string>;

class SudokuModel
{
private:
	int m_board[9][9];
	//Fill with zeroes
	void initBoard();
	//Checks for zeroes/empty cells on the board
	bool noZeroes();	
	//Checks if all the rows are valid
	bool checkRows();
	//Checks if all the cols are valid
	bool checkCols();
	//Checks if all the 3x3 blocks are valid
	bool checkBlocks();

public:
	SudokuModel();
	//A solved board is valid and has no zeroes
	bool solved();
	/*
	Cheks the sudoku rules on the whole board
	All digits can only appear once pro row, column and 3x3 block
	Zeroes/Empty cells don't count!
	That means a half-solved board is still valid, as long as the rules above are not broken
	*/
	bool isValid();
	//String representation of the current board
	std::string toString();
	~SudokuModel();
};

