#include "Board.h"

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

Board::Board()
{
	srand(time(0));

	this->M = 3 + rand() % 4;
	this->N = M + 1;

	setBoard();
}

Board::Board(int M, int N)
{
	this->M = M;
	this->N = N;

	setBoard();
}

Board::Board(int M, int N, std::string input)
{
	board.resize(M * 3 + M + 1, std::vector<char>(N * 3 + N + 1, ' '));
	answer.resize(M, std::vector<bool>(N));

	this->M = M;
	this->N = N;

	this->height = M * 3 + M + 1;
	this->width = N * 3 + N + 1;

	this->startX = 0;
	this->startY = 2;

	this->endX = width - 1;
	this->endY = height - 3;


	int pr = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i % 4 == 0 || j == 0 || j == width - 1)
			{
				continue;
			}
			else
			{
				board[i][j] = input[pr++];
			}
		}
	}

	board[startY][startX] = 'S';
	board[endY][endX] = 'E';

	for (int i = 1; i < height; i += 4)
	{
		std::vector<Pipe>temp;
		for (int j = 1; j < width; j += 4)
		{
			char store[3][3];

			for (int k = i; k < i + 3; k++)
			{
				for (int m = j; m < j + 3; m++)
				{
					if (board[k][m] == 'A')
					{
						answer[k / 4][m / 4] = true;
						board[k][m] = 'P';
					}

					store[k - i][m - j] = board[k][m];
				}
			}

			Pipe set = set.FindKindPipe(store);
			temp.push_back(set);
		}
		PipeBoard.push_back(temp);
	}

	waterPassBFS();
}

Board::~Board()
{
}

void Board::print()
{
	update();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//Change color
			if ((board[i][j] == 'S' || board[i][j] == 'E') && waterPass[i][j])
			{
				SetColor(188);
			}
			else if (board[i][j] != '#' && waterPass[i][j])
			{
				SetColor(187);
			}
			else if ((board[i][j] == '#' || board[i][j] == 'P') && i / 4 == playerY && j / 4 == playerX)
			{
				SetColor(206);
			}
			else if ((board[i][j] == '#' || board[i][j] == 'P') && answer[i / 4][j / 4])
			{
				SetColor(12);
			}
			else
			{
				SetColor();
			}

			if (board[i][j] == 'X')
			{
				std::cout << ' ';
			}
			else
			{
				std::cout << board[i][j];
			}
		}
		std::cout << std::endl;
	}
}

void Board::turnPipe(char dir)
{
	if (dir == 'L')
	{
		PipeBoard[playerY][playerX].TurnLeft();
	}
	else if (dir == 'R')
	{
		PipeBoard[playerY][playerX].TurnRight();
	}
}

void Board::waterPassBFS()
{
	std::vector<std::vector<bool>> temp(height, std::vector<bool>(width, false));
	waterPass = temp;

	struct Node {
		int x, y;
		std::vector<std::pair<int, int>> path;
	};

	std::queue<Node> q;
	q.push({ startX, startY, {{startX, startY}} });
	waterPass[startY][startX] = true;

	int dx[] = { -1, 1, 0, 0 };
	int dy[] = { 0, 0, -1, 1 };

	while (!q.empty())
	{
		Node current = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int newX = current.x + dx[i];
			int newY = current.y + dy[i];
			if (newX >= 0 && newX < width && newY >= 0 && newY < height)
			{
				if ((board[newY][newX] == ' ' || board[newY][newX] == 'X'))
				{
					newX += dx[i];
					newY += dy[i];
				}
			}

			if (isValid(newX, newY, waterPass))
			{
				waterPass[newY][newX] = true;
				auto newPath = current.path;
				newPath.push_back({ newX, newY });
				q.push({ newX, newY, newPath });
			}
		}
	}
}

void Board::playerMove(int deltaX, int deltaY)
{
	if (playerX + deltaX >= 0 && playerX + deltaX < N && playerY + deltaY >= 0 && playerY + deltaY < M)
	{
		playerX += deltaX;
		playerY += deltaY;
	}
}

void Board::findTheOneRoad(int StartX, int StartY, int EndX, int EndY)
{
	std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

	struct Node {
		int x, y;
		std::vector<std::pair<int, int>> path;
	};

	std::queue<Node> q;
	q.push({ StartX, StartY, {{StartX, StartY}} });
	visited[StartY][StartX] = true;

	int dx[] = { -2, 2, 0, 0 };
	int dy[] = { 0, 0, -2, 2 };

	while (!q.empty())
	{
		Node current = q.front();
		q.pop();

		// End found
		if (current.x == EndX && current.y == EndY)
		{
			answer.resize(M, std::vector<bool>(N, false));
			for (auto& p : current.path) {
				if ((p.first - 2) % 4 == 0 && (p.second - 2) % 4 == 0)
					answer[(p.second - 2) / 4][(p.first - 2) / 4] = true;
			}
			return;
		}

		for (int i = 0; i < 4; ++i)
		{
			int newX = current.x + dx[i];
			int newY = current.y + dy[i];

			if (isValid(newX, newY, visited))
			{
				visited[newY][newX] = true;
				auto newPath = current.path;
				newPath.push_back({ newX, newY });
				q.push({ newX, newY, newPath });
			}
		}
	}
}

void Board::pipeToBoard()
{
	for (int i = 1; i < height; i += 4)
	{
		for (int j = 1; j < width; j += 4)
		{
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

void Board::update()
{
	pipeToBoard();
	waterPassBFS();
}

bool Board::checkwin()
{
	return waterPass[endY][endX];
}

void Board::setPipeMap()
{
	for (int i = 2; i < height; i += 4)
	{
		std::vector<Pipe>temp;
		for (int j = 2; j < width; j += 4)
		{
			char up = board[i - 2][j], right = board[i][j + 2], down = board[i + 2][j], left = board[i][j - 2];
			Pipe set = set.SetPipe(up, right, down, left);
			temp.push_back(set);
		}
		PipeBoard.push_back(temp);
	}
}

int direction[5] = { -1,0,1,0,-1 };

void Board::generateMapDFS(int x, int y)
{

	int dx, dy, nx, ny, rdir;
	std::vector<int> dirs = { 0, 1, 2, 3 };
	random_shuffle(dirs.begin(), dirs.end());

	for (int i = 0; i < 4; ++i) {
		rdir = dirs[i];
		dx = direction[rdir];
		dy = direction[rdir + 1];
		nx = x + (dx * 4);
		ny = y + (dy * 4);
		if (nx > 0 && ny > 0 && ny < height - 1 && nx < width - 1 && board[ny][nx] == '#') {
			board[ny - (dy * 2)][nx - (dx * 2)] = 'X';
			board[ny][nx] = 'P';
			generateMapDFS(nx, ny);
		}

	}
}

bool Board::isValid(int x, int y, std::vector<std::vector<bool>>& visited)
{
	if (x >= 0 && x < width && y >= 0 && y < height && (board[y][x] == 'X' || board[y][x] == 'P' || board[y][x] == 'E') && !visited[y][x]) {
		return true;
	}
	return false;
}

void Board::setBoard()
{
	srand(time(0));
	//Add new walls and dividers
	this->height = M * 3 + M + 1;
	this->width = N * 3 + N + 1;

	int position[8][2] = { {0,2},{0,this->width - 3},
							  {2,width - 1}, {height - 3,width - 1},
							  {height - 1,width - 3},{height - 1,2},
							  {height - 3,0},{2,0} };
	int StartToEnd[8][2] = { {0,4},{1,5},{2,6},{3,7},
							 {4,0},{5,1},{6,2},{7,3} };

	int random = rand() % 8;

	this->startX = position[StartToEnd[random][0]][1];
	this->startY = position[StartToEnd[random][0]][0];

	this->endX = position[StartToEnd[random][1]][1];
	this->endY = position[StartToEnd[random][1]][0];

	this->playerX = 0;
	this->playerY = 0;

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

	board[startY][startX] = 'S';
	board[endY][endX] = 'E';

	initializeMap();
}

void Board::initializeMap()
{
	int firstPipeX = startX;
	int firstPipeY = startY;
	int endPipeX = endX;
	int endPipeY = endY;

	if (startX == 0) firstPipeX = 2;
	else if (startX == width - 1) firstPipeX = width - 3;

	if (startY == 0) firstPipeY = 2;
	else if (startY == height - 1) firstPipeY = height - 3;

	if (endX == 0) endPipeX = 2;
	else if (endX == width - 1) endPipeX = width - 3;

	if (endY == 0) endPipeY = 2;
	else if (endY == height - 1) endPipeY = height - 3;

	this->playerX = firstPipeX / 4;
	this->playerY = firstPipeY / 4;

	generateMapDFS(firstPipeX, firstPipeY);
	setPipeMap();
	findTheOneRoad(firstPipeX, firstPipeY, endPipeX, endPipeY);
	waterPassBFS();
}