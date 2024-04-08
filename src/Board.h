#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <ctime>
#include <queue>
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
	void findTheOneRoad(int, int, int, int);

private:
	int M, N;
	int width, height;
	int startX, startY;
	int endX, endY;
	std::vector<std::vector<char>> board;
	std::vector<std::vector<Pipe>> PipeBoard;
	std::vector<std::vector<bool>> answer;
	void generateMapDFS(int, int);
	bool isValid(int, int, std::vector<std::vector<bool>>&);
};
#endif // _BOARD_H_
