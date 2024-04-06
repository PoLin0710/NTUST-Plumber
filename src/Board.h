#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <ctime>
#include <iostream>

class Board
{
public:
	Board();
	~Board();
	void print();

private:
	int M, N;
	int width, height;
	int startX, startY;
	int endX, endY;
	std::vector<std::vector<char>> board;
};
#endif // _BOARD_H_
