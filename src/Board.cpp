#include "Board.h"

Board::Board()
{
	srand(time(0));

	this->M = 3 + rand() % 1;
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
}

void Board::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::generateMap()
{
	int firstPipeX = 0;
	int firstPipeY = 0;

	if (startX == 0)
	{
		firstPipeX = 2;
	}
	else if (startX == width - 1)
	{
		firstPipeX = width - 3;
	}
	else
	{
		firstPipeX = startX;
	}

	if (startY == 0)
	{
		firstPipeY = 2;
	}
	else if (startY == height - 1)
	{
		firstPipeY = height - 3;
	}
	else
	{
		firstPipeY = startY;
	}

	generateMapDFS(firstPipeX, firstPipeY);
}

void Board::setPipeMap()
{
	for (int i = 2; i < height; i += 4)
	{
		std::vector<Pipe>temp;
		for (int j = 2; j < width; j += 4)
		{
			char up = board[i - 2][j], right = board[i][j + 2], down = board[i + 2][j], left = board[i][j - 2];
			Pipe set = set.setPipe(up, right, down, left);
			temp.push_back(set);
		}
		PipeBoard.push_back(temp);
	}
}

int direction[5] = { -1,0,1,0,-1 };

void Board::generateMapDFS(int x, int y)
{

	int dx, dy, nx, ny, rdir;
	std::vector<int> dirs = { 0, 1, 2, 3 };
	random_shuffle(dirs.begin(), dirs.end());

	for (int i = 0; i < 4; ++i) {
		rdir = dirs[i];
		dx = direction[rdir];
		dy = direction[rdir + 1];
		nx = x + (dx * 4);
		ny = y + (dy * 4);
		if (nx > 0 && ny > 0 && ny < height - 1 && nx < width - 1 && board[ny][nx] == '#') {
			board[ny - (dy * 2)][nx - (dx * 2)] = 'X';
			board[ny][nx] = 'P';
			generateMapDFS(nx, ny);
		}

	}
}
