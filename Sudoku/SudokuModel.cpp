#include "SudokuModel.h"
#include <stdio.h>

void SudokuModel::initBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_board[i][j] = 0;
		}
	}
		
}

bool SudokuModel::noZeroes()
{
	return false;
}

bool SudokuModel::checkRows()
{
	return false;
}

bool SudokuModel::checkCols()
{
	return false;
}

bool SudokuModel::checkBlocks()
{
	return false;
}

SudokuModel::SudokuModel()
{
	initBoard();
	printf("Board initialized!\n");
}

bool SudokuModel::solved()
{
	return isValid() && noZeroes();
}


bool SudokuModel::isValid()
{
	return checkBlocks() && checkCols() && checkRows();
}

std::string SudokuModel::toString()
{
	std::string out;
	for (int row = 8; row >= 0; row--) 
	{
		for (int col = 0; col < 9; col++) 
		{
			out += " " + m_board[row][col];
			out += "_|";
		}
		out += "\n";
		if (row > 0 && row < 9) 
		{
			for (int i = 0; i < 9; i++) 
			{
				out += "----";
			}
			out += "\n";
		}
	}
	return out;
}

SudokuModel::~SudokuModel()
{
}
