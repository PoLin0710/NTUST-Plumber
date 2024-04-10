#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <ctime>
#include <queue>
#include <iostream>
#include <algorithm>
#include <windows.h> //º“¿¿GUI
#include "Pipe.h"

class Board
{
public:
	Board();
	Board(int M, int N);
	Board(int M, int N, std::string);
	~Board();
	void print();
	void playerMove(int, int);
	void turnPipe(char);
	void waterPassBFS();
	bool checkwin();

private:
	int M, N;
	int width, height;
	int startX, startY;
	int endX, endY;
	int playerX, playerY;
	std::vector<std::vector<char>> board;
	std::vector<std::vector<Pipe>> PipeBoard;
	std::vector<std::vector<bool>> answer;
	std::vector<std::vector<bool>> waterPass;
	void setBoard();
	void initializeMap();
	void generateMapDFS(int, int);
	void setPipeMap();
	bool isValid(int, int, std::vector<std::vector<bool>>&);
	void findTheOneRoad(int, int, int, int);
	void pipeToBoard();
	void update();

};
#endif // _BOARD_H_
