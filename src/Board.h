/***********************************************************************
 * File: Board.h
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Create Date: 2024-04-07
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-29
 * Description: Header file for the Board class.
***********************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <ctime>
#include <queue>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "Pipe.h"

// Declare Pipe class
class Board
{
public:
	// Constructor
	Board();
	Board(int M, int N);
	Board(int M, int N, std::string);

	// Deconstructor
	~Board();

	// Board function
	void playerMove(int, int);
	void turnPipe(char);
	void waterPassBFS();
	void update();
	bool checkwin();

	//Get Board info
	int getPlayerX();
	int getPlayerY();
	int getRow();
	int getCol();
	int getBegin();
	int getEnd();
	std::vector<std::vector<Pipe>> getPipeBoard();
	std::vector<std::vector<bool>> getAnswer();
	std::vector<std::vector<bool>> getWaterPass();

	// Debug function
	void print();
private:
	// Declare Board Attributes
	int M, N; // Pipe board size M:height N:width
	int width, height; // Print board size
	int startX, startY; // Begin position in board
	int endX, endY; // End Position in board
	int begin, end; // Corresponding developer working directory code name
	int playerX, playerY; // Player in PipeBoard Postion
	std::vector<std::vector<char>> board; // PrintBoard 
	std::vector<std::vector<Pipe>> PipeBoard; // Pipes Board
	std::vector<std::vector<bool>> answer; // Answer for one Road
	std::vector<std::vector<bool>> waterPass; // Store water Pass state

	// Board function
	void setBoard();
	void initializeMap();
	void generateMapDFS(int, int);
	void setPipeMap();
	bool isValid(int, int, std::vector<std::vector<bool>>&);
	void findTheOneRoad(int, int, int, int);
	void pipeToBoard();
};
#endif // _BOARD_H_
