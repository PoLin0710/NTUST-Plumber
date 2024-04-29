/***********************************************************************
 * File: Game.h
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Create Date: 2024-04-08
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-29
 * Description: Header file for the Game class.
***********************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
#include "Board.h"

// Decalre VaildInput
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	EJ = 4,
	EL = 5,
	INVALID,
};

// Declare GameMode
enum GameMode {
	READFILE = 0,
	CUSTOM = 1,
	RANDOM = 2,
	NOTHING = 3
};

//Declare Pipe json object 
struct Json_object {
	int id;
	int type;
	int dir;
	bool flow;
	bool answer;
};

// Declare Game class
class Game
{
public:
	// Constructor
	Game();

	// Deconstructor
	~Game();

	// Game function
	void start(int, int, std::wstring);
	void setMode(char input);
	void ReadMode(std::wstring);
	void CustomMode(int, int);
	void RandomMode();
	void keyUpdate(char input);
	void update();

	// Get game info
	int getPlayer();
	bool getWinStatu();
	bool getSetSatae();
	std::vector<int> getBoardSize();
	std::vector<int> getStartEnd();
	std::vector<Json_object> getStatu();

private:
	// Declare Game Attributes
	int mode;
	Board board;
	bool isWin;
	bool setState;
	bool keyState[7];
	const double gTimeLog = 0.033;
};

#endif // !_GAME_H_
