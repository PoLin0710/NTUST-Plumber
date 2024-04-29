/***********************************************************************
 * File: Board.cpp
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
 * Description: Implementation file for the Board class.
***********************************************************************/
#include "Board.h"

/**
 * Intent: To set the text color in the console.
 * Pre: None.
 * Post: Sets the text color in the console to the specified color value.
 * \param color An integer representing the color value to set. Default is 7 (white).
 */
void SetColor(int color = 7)
{
	// Declare
	HANDLE hConsole;

	//Get
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set Color
	SetConsoleTextAttribute(hConsole, color);
}

/**
 * Intent: To construct a Board object.
 * Pre: None.
 * Post: Initializes a Board object with a random Height between 3 and 6,Width is one more Height.
 */
Board::Board()
{
	srand(time(0));

	this->M = 3 + rand() % 4; // Randomly select a size between 3 and 6 for the Height
	this->N = M + 1; // N is one more than M

	setBoard(); // Call the setBoard function to initialize the board
}

/**
 * Intent: To construct a Board object with specified dimensions.
 * Pre: None.
 * Post: Initializes a Board object with the specified dimensions M and N.
 * \param M The number of Height in the board.
 * \param N The number of Width in the board.
 */
Board::Board(int M, int N)
{
	this->M = M; // Set the number of Height
	this->N = N; // Set the number of Width

	setBoard(); // Call the setBoard function to initialize the board
}

/**
 * Intent: To construct a Board object with specified dimensions and input configuration.
 * Pre: None.
 * Post: Initializes a Board object with the specified dimensions M and N,
 *		 and sets the board configuration based on the input string.
 * \param M The number of rows in the board.
 * \param N The number of columns in the board.
 * \param input A string representing the configuration of the board,
 *		        including pipes, empty spaces, start ('S'), end ('E'), and pipes to connect ('A').
 */
Board::Board(int M, int N, std::string input)
{
	// Resize the board and answer vectors based on the dimensions M and N
	board.resize(M * 3 + M + 1, std::vector<char>(N * 3 + N + 1, ' '));
	answer.resize(M, std::vector<bool>(N));

	this->M = M; // Set the number of Height
	this->N = N; // Set the number of Width

	this->height = M * 3 + M + 1; // Calculate the height of the board
	this->width = N * 3 + N + 1; // Calculate the width of the board

	this->startX = 0; // Set the x-coordinate of the start point
	this->startY = 2; // Set the y-coordinate of the start point

	this->endX = width - 1; // Set the x-coordinate of the end point
	this->endY = height - 3; // Set the y-coordinate of the end point

	this->begin = 7; // Set the begin Number(left upper left)
	this->end = 3; // Set the end Number(right lower right)

	int pr = 0; // Initialize a variable to keep track of the position in the input string

	// Loop through each cell in the board
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// avoid Space
			if (i == 0 || i % 4 == 0 || j == 0 || j == width - 1)
			{
				continue;
			}
			else // read string
			{
				board[i][j] = input[pr++];
			}
		}
	}

	// set start and end to Board
	board[startY][startX] = 'S';
	board[endY][endX] = 'E';

	// Iterate over each pipe block in the board and determine its type
	for (int i = 1; i < height; i += 4)
	{
		std::vector<Pipe>temp;
		for (int j = 1; j < width; j += 4)
		{
			// Extract the 3x3 block of characters representing the pipe
			char store[3][3];

			for (int k = i; k < i + 3; k++)
			{
				for (int m = j; m < j + 3; m++)
				{
					// If the cell contains 'A', mark it as part of the answer and set it to 'P'
					if (board[k][m] == 'A')
					{
						answer[k / 4][m / 4] = true;
						board[k][m] = 'P';
					}

					// Store the character in the block
					store[k - i][m - j] = board[k][m];
				}
			}

			Pipe set = set.FindKindPipe(store); // Determine the type of pipe based on the block configuration
			temp.push_back(set); // Add the pipe to the vector
		}
		PipeBoard.push_back(temp); // Add the vector of pipes to the board
	}

	// Perform a breadth-first search to determine water flow paths
	waterPassBFS();
}

/**
 * Intent: To destruct a Board object.
 * Pre: None.
 * Post: Cleans up resources associated with the Board object.
 */
Board::~Board()
{
}

/**
 * Intent: To print the current state of the board.
 * Pre: None.
 * Post: Displays the board with updated colors and symbols.
 */
void Board::print()
{
	// Update the board state
	update();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Change color based on conditions
			if ((board[i][j] == 'S' || board[i][j] == 'E') && waterPass[i][j])
			{
				SetColor(188); // Set color for start and end points with water
			}
			else if (board[i][j] != '#' && waterPass[i][j])
			{
				SetColor(187); // Set color for paths with water
			}
			else if ((board[i][j] == '#' || board[i][j] == 'P') && i / 4 == playerY && j / 4 == playerX)
			{
				SetColor(206); // Set color for the player's position
			}
			else if ((board[i][j] == '#' || board[i][j] == 'P') && answer[i / 4][j / 4])
			{
				SetColor(12); // Set color for pipes that are part of the solution
			}
			else
			{
				SetColor(); // Reset color to default
			}

			// Print the character at position (i, j) on the board
			if (board[i][j] == 'X')
			{
				std::cout << ' '; // Print space for create Road symbol
			}
			else
			{
				std::cout << board[i][j]; // Print the character at position (i, j)
			}
		}

		std::cout << std::endl; // Move to the next line after printing each row
	}
}

/**
 * Intent: To rotate the pipe at the player's position in the specified direction.
 * Pre: 'dir' must be either 'L' (left) or 'R' (right).
 * Post: Rotates the pipe at the player's position accordingly.
 * \param dir The direction in which to rotate the pipe ('L' for left, 'R' for right).
 */
void Board::turnPipe(char dir)
{
	if (dir == 'L')
	{
		PipeBoard[playerY][playerX].TurnLeft(); // Rotate the pipe left
	}
	else if (dir == 'R')
	{
		PipeBoard[playerY][playerX].TurnRight(); // Rotate the pipe right
	}
}

/**
 * Intent: Perform a breadth-first search (BFS) to determine the path of water flow on the board.
 * Pre: None.
 * Post: Updates the 'waterPass' matrix to mark the positions reachable by water flow.
 */
void Board::waterPassBFS()
{
	// Create a temporary matrix to track visited positions by water flow
	std::vector<std::vector<bool>> temp(height, std::vector<bool>(width, false));
	waterPass = temp;

	// Define a struct for nodes in the BFS traversal
	struct Node {
		int x, y;
		std::vector<std::pair<int, int>> path;
	};

	std::queue<Node> q; // Create a queue for BFS traversal
	q.push({ startX, startY, {{startX, startY}} }); // Start BFS from the start position
	waterPass[startY][startX] = true; // Mark the start position as visited

	// Define the possible movements in the horizontal and vertical directions
	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };


	while (!q.empty())
	{
		Node current = q.front();
		q.pop();

		// Check each direction (up, down, left, right) from the current position
		for (int i = 0; i < 4; ++i)
		{
			int newX = current.x + dx[i];
			int newY = current.y + dy[i];

			// Adjust the new position if it hits an empty space or an create symbol
			if (newX >= 0 && newX < width && newY >= 0 && newY < height)
			{
				if ((board[newY][newX] == ' ' || board[newY][newX] == 'X'))
				{
					newX += dx[i];
					newY += dy[i];
				}
			}

			// Check if the new position is valid and hasn't been visited yet
			if (isValid(newX, newY, waterPass))
			{
				waterPass[newY][newX] = true; // Mark the new position as visited

				auto newPath = current.path;
				newPath.push_back({ newX, newY }); // Add the new position to the current path

				q.push({ newX, newY, newPath }); // Add the new position to the queue
			}
		}
	}
}

/**
 * Intent: Move the player on the board by the specified delta values.
 * Pre: None.
 * Post: Updates the player's position on the board based on the provided delta values.
 * \param deltaX: The change in the player's horizontal position.
 * \param deltaY: The change in the player's vertical position.
 */
void Board::playerMove(int deltaX, int deltaY)
{
	// Check if the new position is within the bounds of the board
	if (playerX + deltaX >= 0 && playerX + deltaX < N && playerY + deltaY >= 0 && playerY + deltaY < M)
	{
		playerX += deltaX; // Update the player's horizontal position
		playerY += deltaY; // Update the player's vertical position
	}
}

/**
 * Intent: Find a path between two points on the board.
 * Pre: None.
 * Post: Finds a path between the specified start and end points on the board and marks it as the correct path.
 * \param StartX: The x-coordinate of the starting point.
 * \param StartY: The y-coordinate of the starting point.
 * \param EndX: The x-coordinate of the ending point.
 * \param EndY: The y-coordinate of the ending point.
 */
void Board::findTheOneRoad(int StartX, int StartY, int EndX, int EndY)
{
	// Create a 2D vector to keep track of visited cells
	std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

	// Define a struct for nodes in the BFS traversal
	struct Node {
		int x, y;
		std::vector<std::pair<int, int>> path;
	};

	std::queue<Node> q; // Create a queue for BFS traversal
	q.push({ StartX, StartY, {{StartX, StartY}} });  // Push the starting node into the queue
	visited[StartY][StartX] = true;  // Mark the starting node as visited

	// Define the possible movements in the horizontal and vertical directions
	int dx[] = { -2, 2, 0, 0 };
	int dy[] = { 0, 0, -2, 2 };

	while (!q.empty())
	{
		// Get the current node from the queue
		Node current = q.front();
		q.pop();

		// End found
		if (current.x == EndX && current.y == EndY)
		{
			// Resize the answer vector to match the dimensions of the board
			answer.resize(M, std::vector<bool>(N, false));

			// Mark the cells along the path as part of the correct path
			for (auto& p : current.path) {
				if ((p.first - 2) % 4 == 0 && (p.second - 2) % 4 == 0)
					answer[(p.second - 2) / 4][(p.first - 2) / 4] = true;
			}

			return;
		}

		// Check if the new position is valid and hasn't been visited yet
		for (int i = 0; i < 4; ++i)
		{
			int newX = current.x + dx[i];
			int newY = current.y + dy[i];

			if (isValid(newX, newY, visited))
			{
				visited[newY][newX] = true; // Mark the new position as visited

				auto newPath = current.path;
				newPath.push_back({ newX, newY }); // Add the new position to the current path

				q.push({ newX, newY, newPath }); // Add the new position to the queue
			}
		}
	}
}

/**
 * Intent: Convert pipes on the PipeBoard to the main board.
 * Pre: None.
 * Post: Updates the main board with the pipes from the PipeBoard.
 */
void Board::pipeToBoard()
{
	// Iterate over the cells of the main board by skipping pipes' positions
	for (int i = 1; i < height; i += 4)
	{
		for (int j = 1; j < width; j += 4)
		{
			// Copy the pipe content from PipeBoard to the corresponding positions on the main board
			for (int k = i; k < i + 3; k++)
			{
				for (int m = j; m < j + 3; m++)
				{
					board[k][m] = PipeBoard[(i - 1) / 4][(j - 1) / 4].pipe[k - i][m - j];
				}
			}
		}
	}
}

/**
 * Intent: Update the main board.
 * Pre: None.
 * Post: Updates the main board with pipes and water flow.
 */
void Board::update()
{
	// Update the main board with pipes from the PipeBoard
	pipeToBoard();
	// Perform BFS to update water flow on the main board
	waterPassBFS();
}

/**
 * Intent: Generate and set pipe objects for the PipeBoard based on the main board.
 * Pre: None.
 * Post: Sets the PipeBoard with appropriate pipe objects based on the configuration of pipes on the main board.
 */
void Board::setPipeMap()
{
	for (int i = 2; i < height; i += 4)
	{
		std::vector<Pipe>temp;

		for (int j = 2; j < width; j += 4)
		{
			// Extract pipe configuration from adjacent cells
			char up = board[i - 2][j], right = board[i][j + 2], down = board[i + 2][j], left = board[i][j - 2];

			// Create a pipe object based on the extracted configuration
			Pipe set = set.SetPipe(up, right, down, left);

			// Add the created pipe object to the temporary vector
			temp.push_back(set);
		}
		// Add the temporary vector of pipe objects to the PipeBoard
		PipeBoard.push_back(temp);
	}
}

// Declare Direction X{-1 ,0 ,1 ,0} Y{0 ,1 ,0 ,-1}
int direction[5] = { -1,0,1,0,-1 };

/**
 * Intent: Generate a map using Depth-First Search (DFS) algorithm.
 * Pre: None.
 * Post: Modifies the board to create a map with pipes based on DFS algorithm.
 * \param x: X-coordinate of the current cell.
 * \param y: Y-coordinate of the current cell.
 */
void Board::generateMapDFS(int x, int y)
{
	int dx, dy, nx, ny, rdir;
	std::vector<int> dirs = { 0, 1, 2, 3 };

	// Randomly shuffle the directions to explore in a random order
	random_shuffle(dirs.begin(), dirs.end());

	for (int i = 0; i < 4; ++i) {
		//Set next target 
		rdir = dirs[i];
		dx = direction[rdir];
		dy = direction[rdir + 1];
		nx = x + (dx * 4);
		ny = y + (dy * 4);

		// Check if the next cell is within bounds and is a wall ('#')
		if (nx > 0 && ny > 0 && ny < height - 1 && nx < width - 1 && board[ny][nx] == '#') {
			// Remove the wall between the current cell and the next cell
			board[ny - (dy * 2)][nx - (dx * 2)] = 'X';

			// Place a pipe in the next cell
			board[ny][nx] = 'P';

			// Recursively call the function to explore the next cell
			generateMapDFS(nx, ny);
		}

	}
}

/**
 * Intent: Check if a cell is valid for water to pass through during BFS traversal.
 * Pre: None.
 * Post: Returns true if the cell is within bounds, is a pipe or an end point, and has not been visited; otherwise, returns false.
 * \param x: X-coordinate of the cell.
 * \param y: Y-coordinate of the cell.
 * \param visited: 2D vector representing visited cells.
 * \return true if the cell is valid, false otherwise.
 */
bool Board::isValid(int x, int y, std::vector<std::vector<bool>>& visited)
{
	// Check the target is legel
	if (x >= 0 && x < width && y >= 0 && y < height && (board[y][x] == 'X' || board[y][x] == 'P' || board[y][x] == 'E') && !visited[y][x]) {
		return true;
	}

	return false;
}

/**
 * Intent: Set up the game board with walls, dividers, start and end points, and initialize the map.
 * Pre: None.
 * Post: Sets up the game board with the specified dimensions, start and end points, and initializes the map.
 */
void Board::setBoard()
{
	srand(time(0));

	this->height = M * 3 + M + 1;
	this->width = N * 3 + N + 1;

	// Define positions of walls, dividers, start, and end points
	int position[8][2] = { {0,2},{0,this->width - 3},
							  {2,width - 1}, {height - 3,width - 1},
							  {height - 1,width - 3},{height - 1,2},
							  {height - 3,0},{2,0} };
	int StartToEnd[8][2] = { {0,4},{1,5},{2,6},{3,7},
							 {4,0},{5,1},{6,2},{7,3} };


	// Randomly select start and end points
	int random = rand() % 8;

	this->begin = StartToEnd[random][0];
	this->end = StartToEnd[random][1];

	this->startX = position[StartToEnd[random][0]][1];
	this->startY = position[StartToEnd[random][0]][0];

	this->endX = position[StartToEnd[random][1]][1];
	this->endY = position[StartToEnd[random][1]][0];

	this->playerX = 0;
	this->playerY = 0;

	// Initialize the board with walls and dividers
	for (int i = 0; i < height; i++)
	{
		std::vector<char> temp;

		for (int j = 0; j < width; j++)
		{
			if (i % 4 == 0 || j % 4 == 0)
			{
				temp.push_back(' ');
			}
			else
			{
				temp.push_back('#');
			}
		}

		board.push_back(temp);
	}

	// Set start and end points on the board
	board[startY][startX] = 'S';
	board[endY][endX] = 'E';

	// Initialize the map
	initializeMap();
}

/**
 * Intent: Initialize the game map, including generating the pipes, setting up the pipe map,
 *		   finding the one road, and updating water pass information.
 * Pre: The board dimensions, start and end points, and player position have been set.
 * Post: Initializes the game map with pipes, sets up the pipe map,
 *		 finds the one road from the start to the end point, and updates water pass information.
 */
void Board::initializeMap()
{
	// Set Begin and End Pipe Position
	int firstPipeX = startX;
	int firstPipeY = startY;
	int endPipeX = endX;
	int endPipeY = endY;

	// Adjust start and end points if they are at the edges of the board
	if (startX == 0) firstPipeX = 2;
	else if (startX == width - 1) firstPipeX = width - 3;

	if (startY == 0) firstPipeY = 2;
	else if (startY == height - 1) firstPipeY = height - 3;

	if (endX == 0) endPipeX = 2;
	else if (endX == width - 1) endPipeX = width - 3;

	if (endY == 0) endPipeY = 2;
	else if (endY == height - 1) endPipeY = height - 3;

	// Set Player Position
	this->playerX = firstPipeX / 4;
	this->playerY = firstPipeY / 4;

	// Generate the map using Depth-First Search algorithm
	generateMapDFS(firstPipeX, firstPipeY);

	// Set up the pipe map
	setPipeMap();

	// Find the one road from start to end point
	findTheOneRoad(firstPipeX, firstPipeY, endPipeX, endPipeY);

	// Update water pass information using Breadth-First Search algorithm
	waterPassBFS();
}

/**
 * Intent: Check if the player has won the game.
 * Pre: None.
 * Post: Returns true if the water has passed through the end point,
 *		 indicating the player has won; otherwise, returns false.
 */
bool Board::checkwin()
{
	return waterPass[endY][endX];
}

/**
 * Intent: Get the x-coordinate of the player's position on the board.
 * Pre: None.
 * Post: Returns the x-coordinate of the player's position.
 */
int Board::getPlayerX()
{
	return playerX;
}

/**
 * Intent: Get the y-coordinate of the player's position on the board.
 * Pre: None.
 * Post: Returns the y-coordinate of the player's position.
 */
int Board::getPlayerY()
{
	return playerY;
}

/**
 * Intent: Get the number of Height in the board.
 * Pre: None.
 * Post: Returns the number of Height in the board.
 */

int Board::getRow()
{
	return M;
}

/**
 * Intent: Get the number of Width in the board.
 * Pre: None.
 * Post: Returns the number of Width in the board.
 */
int Board::getCol()
{
	return N;
}

/**
 * Intent: Get the index of the starting point.
 * Pre: None.
 * Post: Returns the index of the starting point.
 */
int Board::getBegin()
{
	return begin;
}

/**
 * Intent: Get the index of the ending point.
 * Pre: None.
 * Post: Returns the index of the ending point.
 */
int Board::getEnd()
{
	return end;
}

/**
 * Intent: Get the pipe board containing the types of pipes.
 * Pre: None.
 * Post: Returns the pipe board containing the types of pipes.
 */
std::vector<std::vector<Pipe>> Board::getPipeBoard()
{
	return PipeBoard;
}

/**
 * Intent: Get the answer indicating the correct orientation of pipes.
 * Pre: None.
 * Post: Returns the answer indicating the correct orientation of pipes.
 */
std::vector<std::vector<bool>> Board::getAnswer()
{
	return answer;
}

/**
 * Intent: Get the water pass information.
 * Pre: None.
 * Post: Returns the water pass information.
 */
std::vector<std::vector<bool>> Board::getWaterPass()
{
	return waterPass;
}