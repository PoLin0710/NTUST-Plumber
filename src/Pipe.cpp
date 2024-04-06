#include "Pipe.h"

Pipe::Pipe()
{
	this->type = PipeType::STRAIGHTPIPE;
	this->dir = Dir::UP;

	for (int i = 0; i < 3; i++)
	{
		pipe[i][0] = '#';
		pipe[i][1] = 'P';
		pipe[i][2] = '#';
	}

}

Pipe::~Pipe()
{
}

Pipe::Pipe(int type)
{
	this->type = type;
	this->dir = Dir::UP;

	for (int i = 0; i < 3; i++)
	{
		pipe[i][0] = '#';
		pipe[i][1] = 'P';
		pipe[i][2] = '#';
	}

	switch (type)
	{
	case PipeType::STRAIGHTPIPE:
		break;
	case PipeType::TPIPE:
		pipe[1][0] = 'P';
		pipe[1][2] = 'P';
		pipe[2][1] = '#';
		break;
	case PipeType::LPIPE:
		pipe[2][1] = '#';
		pipe[1][2] = 'P';
		break;
	case PipeType::CROSSPIPE:
		pipe[1][0] = 'P';
		pipe[1][2] = 'P';
		break;
	default:
		break;
	}

}

void Pipe::print()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << pipe[i][j];
		}
		std::cout << std::endl;
	}
}

void Pipe::TurnRight()
{
	this->dir = (this->dir + 1) % 4;

	char temp[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = pipe[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pipe[i][j] = temp[2 - j][i];
		}
	}
}

void Pipe::TurnLeft()
{
	this->dir = (this->dir - 1) < 0 ? 3 : this->dir - 1;

	char temp[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = pipe[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pipe[i][j] = temp[j][2 - i];
		}
	}
}
