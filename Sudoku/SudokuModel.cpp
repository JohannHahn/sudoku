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
			if (col % 3 == 0)
			{
				out += "|";
			}
			out += " ";
			//ASCII
			out += '0' + m_board[row][col];			
			out += " |";
		}
		out += "\n";
		if (row > 0 && row < 9) 
		{
			if (row % 3 == 0)
			{
				out += "\n";
			}
			
			for (int i = 0; i < 9; i++) 
			{
				//out += "----";
			}
			out += "\n";
		}
	}
	return out;
}

SudokuModel::~SudokuModel()
{
}
