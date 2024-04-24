#include "Game.h"

Game::Game()
{
	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		keyState[i] = false;
	}

	mode = GameMode::NOTHING;

}

Game::~Game()
{
}

void Game::start(int M, int N)
{

	if (mode == GameMode::READFILE)
	{
		ReadMode();
	}
	else if (mode == GameMode::CUSTOM)
	{
		CustomMode(M, N);
	}
	else if (mode == GameMode::RANDOM)
	{
		RandomMode();
	}

}

void Game::setMode(char input)
{
	switch (input)
	{
	case'1':
		mode = GameMode::READFILE;
		break;
	case'2':
		mode = GameMode::CUSTOM;
		break;
	case'3':
		mode = GameMode::RANDOM;
		break;
	}
}

void Game::ReadMode()
{
	std::ifstream inFile("../../src/map/map1.txt");

	int m = 0, n = 0;
	std::string temp = "", input;

	inFile >> m >> n;

	while (getline(inFile, input))
	{
		temp += input;
	}

	Board ans(m, n, temp);
	board = ans;
}

void Game::CustomMode(int Row, int Col)
{
	Board ans(Row, Col);
	board = ans;
}

void Game::RandomMode()
{
	Board map;
	board = map;
}

void Game::keyUpdate(char input)
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		keyState[i] = false;
	}
	switch (input) {
	case 'w':
	case 'W':
		keyState[ValidInput::EW] = true;
		break;
	case 's':
	case 'S':
		keyState[ValidInput::ES] = true;
		break;
	case 'a':
	case 'A':
		keyState[ValidInput::EA] = true;
		break;
	case 'd':
	case 'D':
		keyState[ValidInput::ED] = true;
		break;
	case 'j':
	case 'J':
		keyState[ValidInput::EJ] = true;
		break;
	case 'l':
	case 'L':
		keyState[ValidInput::EL] = true;
		break;
	default:
		break;
	}
}

void Game::update()
{
	// ¬O§_¦³input
	bool hasInput = false;
	if (keyState[ValidInput::EW])
	{
		board.playerMove(0, -1);
		hasInput = true;
	}
	else if (keyState[ValidInput::ES])
	{
		board.playerMove(0, 1);
		hasInput = true;
	}
	else if (keyState[ValidInput::EA])
	{
		board.playerMove(-1, 0);
		hasInput = true;
	}
	else if (keyState[ValidInput::ED])
	{
		board.playerMove(1, 0);
		hasInput = true;
	}
	else if (keyState[ValidInput::EJ])
	{
		board.turnPipe('L');
		hasInput = true;
	}
	else if (keyState[ValidInput::EL])
	{
		board.turnPipe('R');
		hasInput = true;
	}

	//board.print();
	isWin = board.checkwin();

}

std::vector<int> Game::getBoardSize()
{
	return { board.getRow(), board.getCol() };
}

bool Game::getWinStatu()
{
	return board.checkwin();
}

std::vector<int> Game::getPlayer()
{
	return { board.getPlayerX(),board.getPlayerY() };
}

std::vector<int> Game::getStartEnd()
{
	return { board.getBegin(), board.getEnd() };
}

std::vector<Json_object> Game::getStatu()
{
	std::vector<Json_object> store;
	std::vector<std::vector<Pipe>> PipeBoard = board.getPipeBoard();
	std::vector<std::vector<bool>> answerBoard = board.getAnswer();
	std::vector<std::vector<bool>> waterPass = board.getWaterPass();

	for (int i = 0; i < board.getRow(); i++)
	{
		for (int j = 0; j < board.getCol(); j++)
		{
			int id = i * board.getCol() + j;
			int type = PipeBoard[i][j].getType();
			int dir = PipeBoard[i][j].getdir();
			bool flow = waterPass[2 + i * 4][2 * j + 4];
			bool answer = answerBoard[i][j];

			store.push_back({ id,type,dir,flow,answer });
		}
	}


	return store;
}