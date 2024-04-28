#ifndef _GAME_H_
#define _GAME_H_

#include <thread>
#include <iostream>
#include <fstream>
#include <string>
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
	RANDOM = 2,
	NOTHING = 3
};

struct Json_object {
	int id;
	int type;
	int dir;
	bool flow;
	bool answer;
};

class Game
{
public:
	Game();
	~Game();
	void start(int, int, std::wstring);
	void setMode(char input);
	void ReadMode(std::wstring);
	void CustomMode(int, int);
	void RandomMode();

	void keyUpdate(char input);
	void update();

	int getPlayer();
	bool getWinStatu();
	bool getSetSatae();
	std::vector<int> getBoardSize();
	std::vector<int> getStartEnd();
	std::vector<Json_object> getStatu();

private:
	bool keyState[7];
	const double gTimeLog = 0.033;
	Board board;
	int mode;
	bool isWin;
	bool setState;
};

#endif // !_GAME_H_
