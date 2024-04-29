/***********************************************************************
 * File: Game.cpp
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Create Date: 2024-04-29
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-30
 * Description: Implementation file for the Game class.
***********************************************************************/

#include "Game.h"

/**
 * Intent: Initialize a new game.
 * Pre: None.
 * Post: Initializes the game with all key states set to false and the mode set to NOTHING.
 */
Game::Game()
{
	//Initializes Keystate
	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		keyState[i] = false;
	}

	//Initializes mode
	mode = GameMode::NOTHING;
}

/**
 * Intent: Destructor for the Game class.
 * Pre: None.
 * Post: Cleans up resources used by the Game object.
 */
Game::~Game()
{
}

/**
 * Intent: Starts the game with the specified parameters.
 * Pre: None.
 * Post: Initiates the game based on the selected mode and parameters.
 * \param M The number of rows in the game board.
 * \param N The number of columns in the game board.
 * \param filename The filename if the game is in read mode.
 */
void Game::start(int M, int N, std::wstring filename)
{
	// Initializes game create state
	setState = true;

	// Choose mode
	if (mode == GameMode::READFILE)
	{
		ReadMode(filename);
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

/**
 * Intent: Sets the game mode based on user input.
 * Pre: None.
 * Post: Updates the game mode according to the user's choice.
 * \param input The user's input indicating the desired game mode.
 */
void Game::setMode(char input)
{
	// Choose mode
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

/**
 * Intent: Reads the game board from a file and initializes the game.
 * Pre: The input file exists and is formatted correctly.
 * Post: Initializes the game board based on the input file.
 * \param infilename The name of the input file containing the game board.
 */
void Game::ReadMode(std::wstring infilename)
{
	std::string fileHeader = "map\\";
	std::string filename;

	// Convert infilename from wide string to string
	for (int i = 0; i < infilename.size(); i++)
	{
		filename.push_back(infilename[i]);
	}

	// Concatenate file header and filename
	filename = fileHeader + filename;

	// Open input file
	std::ifstream inFile(filename);

	// Check the file can open
	if (!inFile.is_open())
	{
		setState = false;
		std::cout << "Error: Unable to open file\n";
		return;
	}

	int m = 0, n = 0;
	std::string temp = "", input;

	// Read dimensions of the game board
	inFile >> m >> n;

	// Read remaining lines to construct the game board
	while (getline(inFile, input))
	{
		temp += input;
	}

	// Initialize the game board with the read data
	Board ans(m, n, temp);
	board = ans;
}

/**
 * Intent: Initializes the game board with custom dimensions.
 * Pre: Row and Col are within the valid range (3 to 15).
 * Post: Initializes the game board with custom dimensions.
 * \param Row The number of rows for the game board.
 * \param Col The number of columns for the game board.
 */
void Game::CustomMode(int Row, int Col)
{
	// Check if dimensions are within valid range
	if (Row < 3 || Row > 15 || Col < 3 || Col > 15)
	{
		setState = false;
		return;
	}

	// Initialize the game board with custom dimensions
	Board ans(Row, Col);
	board = ans;
}

/**
 * Intent: Initializes the game board with random dimensions and layout.
 * Pre:
 * Post: Initializes the game board with random dimensions and layout.
 */
void Game::RandomMode()
{
	// Initialize the game board with random dimensions and layout
	Board map;
	board = map;
}

/**
 * Intent: Updates the game's keyboard input state based on the given input.
 * Pre: Input is a character representing a keyboard input.
 * Post: Updates the game's keyboard input state based on the given input.
 * \param input: A character representing a keyboard input.
 */
void Game::keyUpdate(char input)
{
	// Reset all key states to false
	for (int i = 0; i < ValidInput::INVALID; i++) {
		keyState[i] = false;
	}

	// Update key states based on the input
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

/**
 * Intent: Updates the game state based on the keyboard input.
 * Pre: The game object has been initialized.
 * Post: Updates the game state based on the keyboard input.
 */
void Game::update()
{
	// Check if there is any keyboard input
	bool hasInput = false;

	if (keyState[ValidInput::EW])
	{
		board.playerMove(0, -1); // Move the player up
		hasInput = true;
	}
	else if (keyState[ValidInput::ES])
	{
		board.playerMove(0, 1); // Move the player down
		hasInput = true;
	}
	else if (keyState[ValidInput::EA])
	{
		board.playerMove(-1, 0); // Move the player left
		hasInput = true;
	}
	else if (keyState[ValidInput::ED])
	{
		board.playerMove(1, 0); // Move the player right
		hasInput = true;
	}
	else if (keyState[ValidInput::EJ])
	{
		board.turnPipe('L'); // Turn the pipe left
		hasInput = true;
	}
	else if (keyState[ValidInput::EL])
	{
		board.turnPipe('R'); // Turn the pipe right
		hasInput = true;
	}

	// Update the board state
	board.update();

	// Check if the player has won
	isWin = board.checkwin();
}

/**
 * Intent: Returns the size of the game board.
 * Pre: The game object has been initialized.
 * Post: Returns a vector containing the number of rows and columns of the game board.
 * \return A vector containing the number of rows and columns of the game board.
 */
std::vector<int> Game::getBoardSize()
{
	return { board.getRow(), board.getCol() };
}

/**
 * Intent: Returns the win status of the game.
 * Pre: The game object has been initialized.
 * Post: Returns true if the player has won the game, false otherwise.
 * \return True if the player has won the game, false otherwise.
 */
bool Game::getWinStatu()
{
	return board.checkwin();
}

/**
 * Intent: Returns the state of the game setup.
 * Pre: The game object has been initialized.
 * Post: Returns true if the game setup was successful, false otherwise.
 * \return True if the game setup was successful, false otherwise.
 */
bool Game::getSetSatae()
{
	return setState;
}

/**
 * Intent: Returns the player's position on the game board.
 * Pre: The game object has been initialized.
 * Post: Returns the index of the player's position on the game board.
 * \return The index of the player's position on the game board.
 */
int Game::getPlayer()
{
	return { board.getPlayerX() + board.getPlayerY() * board.getCol() };
}

/**
 * Intent: Returns the start and end points of the game board.
 * Pre: The game object has been initialized.
 * Post: Returns a vector containing the start and end points of the game board.
 * \return A vector containing the start and end points of the game board.
 */
std::vector<int> Game::getStartEnd()
{
	return { board.getBegin(), board.getEnd() };
}

/**
 * Intent: Returns the status of each cell on the game board.
 * Pre: The game object has been initialized.
 * Post: Returns a vector of JSON objects representing the status of each cell on the game board.
 * \return A vector of JSON objects representing the status of each cell on the game board.
 */
std::vector<Json_object> Game::getStatu()
{
	// Declare json vector
	std::vector<Json_object> store;

	// Get board info
	std::vector<std::vector<Pipe>> PipeBoard = board.getPipeBoard();
	std::vector<std::vector<bool>> answerBoard = board.getAnswer();
	std::vector<std::vector<bool>> waterPass = board.getWaterPass();

	// Store to json vector
	for (int i = 0; i < board.getRow(); i++)
	{
		for (int j = 0; j < board.getCol(); j++)
		{
			int id = i * board.getCol() + j;
			int type = PipeBoard[i][j].getType();
			int dir = PipeBoard[i][j].getdir();
			bool flow = waterPass[2 + i * 4][2 + j * 4];
			bool answer = answerBoard[i][j];

			store.push_back({ id,type,dir,flow,answer });
		}
	}

	return store;
}