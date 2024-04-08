#include "Game.h"

Game::Game()
{
	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		keyState[i] = false;
	}
}

Game::~Game()
{
}

void Game::start()
{
	while (1)
	{
		system("cls");
		setMode();

		if (mode == GameMode::CUSTOM)
		{
			CustomMode();
		}
		else if (mode == GameMode::RANDOM)
		{
			RandomMode();
		}

		clock_t startT, endT;
		startT = 0;
		endT = 100;

		isWin = false;

		do
		{
			double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

			if (timeFrame >= gTimeLog) {
				update();
				startT = clock();
			}

			if (isWin == false)
			{
				keyUpdate();
				endT = clock();
			}
		} while (!isWin);

		std::cout << "Stage Clear!\n";

		char input = '1';
		do
		{
			if (input != '1' && input != '2')
			{
				std::cout << "Invailed Input\n";
			}
			std::cout << "Want to play again?\n";
			std::cout << "1. Yes\n";
			std::cout << "2. No\n";
			input = _getch();
			system("cls");
		} while (input != '1' && input != '2');

		if (input == '1')
		{
			continue;
		}
		else
		{
			system("cls");
			std::cout << "Bye bye~";
			break;
		}
	}
}

void Game::setMode()
{
	while (1)
	{
		std::cout << "Choose Mode\n";
		std::cout << "1. Read File\n";
		std::cout << "2. Custom\n";
		std::cout << "3. Random\n";

		char input = _getch();
		if (input >= '1' && input <= '3')
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

			system("cls");
			break;
		}
		else
		{
			system("cls");
			std::cout << "Error input!!\n";
		}

	}

}

void Game::CustomMode()
{
	int Row, Col;
	while (1)
	{

		std::cout << "Input Row(3<=ROW<=15) : ";
		std::cin >> Row;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			system("cls");
			std::cout << "Invailed Input" << std::endl;
			continue;
		}


		std::cout << "Input Col(3<=COL<=15) : ";
		std::cin >> Col;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			system("cls");
			std::cout << "Invailed Input" << std::endl;
			continue;
		}

		if (Row >= 3 && Row <= 15 && Col >= 3 && Col <= 15)
		{
			Board ans(Row, Col);
			board = ans;

			break;
		}
		else
		{
			std::cin.ignore();
			std::cin.clear();

			system("cls");
			std::cout << "Error input!!\n";
		}

	}
}

void Game::RandomMode()
{
	Board map;
	board = map;
}

void Game::keyUpdate()
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		keyState[i] = false;
	}
	char input = _getch();
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
	system("cls");
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

	board.print();
	isWin = board.checkwin();

}
