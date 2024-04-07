#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Pipe.h"

class Board
{
public:
	Board();
	~Board();
	void print();
	void generateMap();
	void setPipeMap();

private:
	int M, N;
	int width, height;
	int startX, startY;
	int endX, endY;
	std::vector<std::vector<char>> board;
	std::vector<std::vector<Pipe>> PipeBoard;
	void generateMapDFS(int, int);
};
#endif // _BOARD_H_
