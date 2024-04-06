#include "Board.h"

Board::Board()
{
	srand(time(0));

	this->M = 3 + rand() % 6;
	this->N = M + 1;

	//Add new walls and dividers
	this->height = M * 3 + M + 1;
	this->width = N * 3 + N + 1;

	int position[8][2] = { {0,2},{0,this->width - 3},
							  {2,width - 1}, {height - 3,width - 1},
							  {height - 1,width - 3},{height - 1,2},
							  {height - 3,0},{2,0} };
	int StartToEnd[8][2] = { {0,4},{1,5},{2,6},{3,7},
							 {4,0},{5,1},{6,2},{7,3} };

	int random = rand() % 8;

	this->startX = position[StartToEnd[random][0]][1];
	this->startY = position[StartToEnd[random][0]][0];

	this->endX = position[StartToEnd[random][1]][1];
	this->endY = position[StartToEnd[random][1]][0];

	for (int i = 0; i < height; i++)
	{
		std::vector<char> temp;
		for (int j = 0; j < width; j++)
		{
			if (i % 4 == 0 || j % 4 == 0)
			{
				temp.push_back(' ');
			}
			else
			{
				temp.push_back('#');
			}

		}
		board.push_back(temp);
	}

	board[startY][startX] = 'S';
	board[endY][endX] = 'E';
}

Board::~Board()
{
	for (int i = 0; i < height; i++)
	{
		std::vector<char> temp;
		for (int j = 0; j < width; j++)
		{
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::print()
{
}
