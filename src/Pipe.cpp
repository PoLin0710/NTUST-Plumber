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

Pipe Pipe::SetPipe(char up, char right, char down, char left)
{
	int roadSum = 0;
	if (up != ' ')roadSum++;
	if (right != ' ')roadSum++;
	if (down != ' ')roadSum++;
	if (left != ' ')roadSum++;

	if (roadSum == 4)
	{
		Pipe result(PipeType::CROSSPIPE);
		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}
		return result;
	}
	else if (roadSum == 3)
	{
		Pipe result(PipeType::TPIPE);
		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}
		return result;
	}
	else if (roadSum == 2)
	{
		if ((up != ' ' && down != ' ') || (left != ' ') && (right != ' '))
		{
			Pipe result(PipeType::STRAIGHTPIPE);
			for (int i = 0; i < rand() % 4; i++)
			{
				result.TurnRight();
			}
			return result;
		}
		else
		{
			Pipe result(PipeType::LPIPE);
			for (int i = 0; i < rand() % 4; i++)
			{
				result.TurnRight();
			}
			return result;
		}
	}
	else
	{
		Pipe result(rand() % 4);
		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}
		return result;
	}

}

Pipe Pipe::FindKindPipe(char src[3][3])
{
	Pipe StraightPipe(PipeType::STRAIGHTPIPE);
	Pipe TPipe(PipeType::TPIPE);
	Pipe LPipe(PipeType::LPIPE);
	Pipe CrossPipe(PipeType::CROSSPIPE);

	for (int i = 0; i < 4; i++)
	{
		bool same = true;

		for (int j = 0; j < 3 && same; j++)
		{
			for (int k = 0; k < 3 && same; k++)
			{
				if (StraightPipe.pipe[j][k] != src[j][k])
				{
					same = false;
				}
			}
		}

		if (same)
		{
			return StraightPipe;
		}
		else
		{
			StraightPipe.TurnRight();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		bool same = true;

		for (int j = 0; j < 3 && same; j++)
		{
			for (int k = 0; k < 3 && same; k++)
			{
				if (TPipe.pipe[j][k] != src[j][k])
				{
					same = false;
				}
			}
		}

		if (same)
		{
			return TPipe;
		}
		else
		{
			TPipe.TurnRight();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		bool same = true;

		for (int j = 0; j < 3 && same; j++)
		{
			for (int k = 0; k < 3 && same; k++)
			{
				if (LPipe.pipe[j][k] != src[j][k])
				{
					same = false;
				}
			}
		}

		if (same)
		{
			return LPipe;
		}
		else
		{
			LPipe.TurnRight();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		bool same = true;

		for (int j = 0; j < 3 && same; j++)
		{
			for (int k = 0; k < 3 && same; k++)
			{
				if (CrossPipe.pipe[j][k] != src[j][k])
				{
					same = false;
				}
			}
		}

		if (same)
		{
			return CrossPipe;
		}
		else
		{
			CrossPipe.TurnRight();
		}
	}
}

int Pipe::getType()
{
	return type;
}

int Pipe::getdir()
{
	return dir;
}
