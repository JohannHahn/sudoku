#include "SudokuModel.h"
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h> //rand
#include <time.h>

//Blocks that can be filled with 1-9 without interfering with each other
int independantBlocks[6][3] =
{
	{0, 4, 8}, {0, 5, 7}, {1, 5, 6},
	{1, 3, 8}, {2, 3, 7}, {2, 4, 6}
	
};

std::vector<std::vector<std::set<int>>> oldCandidates;
std::vector<std::set<int>> candidates;

bool compareSetBySize(std::set<int> a, std::set<int> b)
{
	return a.size() < b.size();
}

//chooses random independant blocks
void chooseBlocks(int b, int *blocks)
{
	int i = rand() % 2;

	switch (b)
	{
	case 0:
		break;
	case 1:
		i += 2;
		break;
	case 2:
		i += 4;
		break;
	case 3:
		i += 3;
		break;
	case 4: 
		i = i == 0 ? 0 : 5;
		break;
	case 5:
		i += 1;
		break;
	case 6:
		i = i == 0 ? 2 : 5;
		break;
	case 7:
		i = i == 0 ? 1 : 4;
		break;
	case 8:
		i = i == 0 ? 0 : 3;
		break;
	}
	memcpy(blocks, &independantBlocks[i][0], sizeof(int) * 3);
}

void SudokuModel::clearBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_board[i][j] = 0;
		}
	}
}

void SudokuModel::newBoard()
{
	//Fill 3 independant blocks (no same row/col) with random permutations of 1-9
	//random block 0-8
	srand(time(NULL));
	int rb = rand() % 9;
	//choose blocks to fill randomly
	int blocks[3];
	chooseBlocks(rb, &blocks[0]);
	//Fill with random permutation;
	//Go through the 3 blocks
	for (int block = 0; block < 3; block++)
	{
		std::set<int> digits = { 1,2,3,4,5,6,7,8,9 };
		//pick 9 random digits from the digits set
		for (int i = 0; i < 9; i++)
		{
			//each iteration the set gets smaller by 1
			int d = rand() % (9 - i);
			//need iterator because sets don't support []
			std::set<int>::iterator it = digits.begin();
			for (int j = 0; j < d; j++)
			{
				it++;
			}
			//compute coordinates on the board
			int x = blocks[block] % 3 * 3 + (i % 3);
			int y = blocks[block] / 3 * 3 + (i / 3);
			//erase the random value from digits and write to block
			m_board[y][x] = *it;
			digits.erase(*it);
		}
	}
	//while (board not filled)
	//Find candidates for each field
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			candidates.push_back(findCandidates(col, row));
		}
	}
	//Sort empty fields by lowest candidate amout
	std::sort(candidates.begin(), candidates.end(), compareSetBySize);

	//if no candidates - go back to previous oldCandidates

	//save current candidates to oldCandidates, might be needed later	
	oldCandidates.push_back(candidates);

	//take first candidate from first non empty candidate list and fill the field with the value

	//loop back

	printf("%d\n", isValid());
}


void SudokuModel::initBoard()
{
	clearBoard();
	newBoard();
}

bool SudokuModel::noZeroes()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (m_board[row][col] == 0) return false;
		}
	}
	return true;
}

bool SudokuModel::checkRows()
{
	for (int row = 0; row < 9; row++)
	{
		//save unique digits in row
		std::set<int> digits = {};
		for (int col = 0; col < 9; col++)
		{
			int a = m_board[row][col];
			//duplicate digit found
			if (a != 0 && digits.find(a) != digits.end())
			{
				return false;
			}
			//unique digit found
			digits.insert(a);
		}
	}
	return true;
}

bool SudokuModel::checkCols()
{
	for (int col = 0; col < 9; col++)
	{
		//save unique digits in row
		std::set<int> digits = {};
		for (int row = 0; row < 9; row++)
		{
			int a = m_board[row][col];
			//duplicate digit
			if (a != 0 && digits.find(a) != digits.end())
			{
				return false;
			}
			//unique digit
			digits.insert(a);
		}
	}
	return true;	
}

bool SudokuModel::checkBlocks()
{
	for (int block = 0; block < 9; block++)
	{
		std::set<int> digits = {};
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				int a = m_board[block / 3 * 3 + y][block % 3 * 3 + x];
				if (a != 0 && digits.find(a) != digits.end())
				{
					return false;
				}
				digits.insert(a);
			}
		}
	}
	return true;	
}

std::set<int> SudokuModel::findCandidates(int x, int y)
{
	//Field not empty
	if (m_board[y][x] != 0)
	{
		printf("Field not empty!\n");
		std::set<int> a = {};
		return a;
	}
	//At first all digits are candidated
	std::set<int> cnds = { 1,2,3,4,5,6,7,8,9 };	
	//check rows, cols and blocks and remove candidates
	//rows
	for (int row = 0; row < 9; row++)
	{
		cnds.erase(m_board[row][x]);
	}	
	//cols
	for (int col = 0; col < 9; col++)
	{
		cnds.erase(m_board[y][col]);
	}
	//block
	int block = x / 3 + (y / 3) * 3;
	int startx = block % 3 * 3;
	int starty = block / 3 * 3;
	for (int i = starty; i < 3 + starty; i++)
	{
		for (int j = startx; j < 3 + startx; j++)
		{
			cnds.erase(m_board[i][j]);
		}
	}
	return cnds;
}

void SudokuModel::setField(int x, int y, int value)
{
	if (x >= 0 && x < 9 && y >= 0 && y < 9 && value > 0 && value <= 9)
	{
		m_board[y][x] = value;
	}
	else
	{
		printf("Wrong Input!\n");
	}
	
}

SudokuModel::SudokuModel()
{
	initBoard();
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
