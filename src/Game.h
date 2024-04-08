#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <conio.h>
#include <ctime>
#include "Board.h"

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

enum GameMode {
	READFILE = 0,
	CUSTOM = 1,
	RANDOM = 2
};

class Game
{
public:
	Game();
	~Game();
	void start();
	void setMode();
	void CustomMode();
	void RandomMode();

	void keyUpdate();
	void update();

private:
	bool keyState[7];
	const double gTimeLog = 0.033;
	Board board;
	int mode;
	bool isWin;
};

#endif // !_GAME_H_
