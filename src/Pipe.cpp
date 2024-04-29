/***********************************************************************
 * File: Pipe.cpp
 * Author:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 *
 * Create Date: 2024-04-07
 * Editor:
 *		B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *		B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *		B11215008 ¬x§B¿o (n590762743@gmail.com)
 *		B11215012 Henry Liu (rov20031214@gmail.com)
 * Update Date: 2024-04-29
 * Description: Implementation file for the Pipe class.
***********************************************************************/

#include "Pipe.h"

/**
 * Intent: To initialize a Pipe object with default values.
 * Pre: None.
 * Post:
 * The Pipe object is initialized with the type STRAIGHTPIPE and direction UP,
 * and the pipe array is filled with STRAIGHTPIPE icon.
 */
Pipe::Pipe()
{
	// Set value to this class
	this->type = PipeType::STRAIGHTPIPE;
	this->dir = Dir::UP;

	// Set Pipe icon
	for (int i = 0; i < 3; i++)
	{
		pipe[i][0] = '#';
		pipe[i][1] = 'P';
		pipe[i][2] = '#';
	}

}

/**
 * Intent: To destruct a Pipe object.
 * Pre: None.
 * Post: The Pipe object is destructed.
 */
Pipe::~Pipe()
{
}

/**
 * Intent: To construct a Pipe object with a specified type.
 * Pre: The parameter 'type' must be a valid PipeType enum value.
 * Post: A Pipe object is constructed with the specified type.
 * \param type The type of the pipe to be constructed.
 */
Pipe::Pipe(int type)
{
	// Set value to this class
	this->type = type;
	this->dir = Dir::UP;

	// Set initialization Pipe icon
	for (int i = 0; i < 3; i++)
	{
		pipe[i][0] = '#';
		pipe[i][1] = 'P';
		pipe[i][2] = '#';
	}

	// Change to corresponding Pipe
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

/**
 * Intent: To print the representation of the Pipe.
 * Pre: None.
 * Post: The Pipe object's representation is printed to the console.
 */
void Pipe::print()
{
	// Print PipeBoard
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << pipe[i][j];
		}
		std::cout << std::endl;
	}
}

/**
 * Intent: To rotate the Pipe object to the right.
 * Pre: None.
 * Post: The Pipe object's orientation is turned clockwise by 90 degrees.
 */
void Pipe::TurnRight()
{
	//Update the direction
	this->dir = (this->dir + 1) % 4;

	// Declare temp board store Pipe
	char temp[3][3];

	// copy PipeBoard to temp
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = pipe[i][j];
		}
	}

	// Rotate 90 from PipeBoard
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pipe[i][j] = temp[2 - j][i];
		}
	}
}

/**
 * Intent: To rotate the Pipe object to the left.
 * Pre: None.
 * Post: The Pipe object's orientation is turned clockwise by -90 degrees.
 */
void Pipe::TurnLeft()
{
	// Update the direction
	this->dir = (this->dir - 1) < 0 ? 3 : this->dir - 1;

	// Declare temp board store Pipe
	char temp[3][3];

	// copy PipeBoard to temp
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = pipe[i][j];
		}
	}

	// Rotate -90 from PipeBoard
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pipe[i][j] = temp[j][2 - i];
		}
	}
}

/**
 * Intent: To create a new Pipe object based on the provided road connections.
 * Pre: None.
 * Post: Returns a new Pipe object with the specified road connections.
 * \param up The character representing the road connection at the top of the pipe.
 * \param right The character representing the road connection at the right side of the pipe.
 * \param down The character representing the road connection at the bottom of the pipe.
 * \param left The character representing the road connection at the left side of the pipe.
 * \return A new Pipe object configured based on the provided road connections.
 */
Pipe Pipe::SetPipe(char up, char right, char down, char left)
{
	//Declare
	int roadSum = 0;

	// Calculate the total number of road connections
	if (up != ' ')roadSum++;
	if (right != ' ')roadSum++;
	if (down != ' ')roadSum++;
	if (left != ' ')roadSum++;

	// Determine the type of the pipe based on the road connections
	if (roadSum == 4)  // Cross Pipe
	{
		Pipe result(PipeType::CROSSPIPE);

		//Random Turn
		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}

		return result;
	}
	else if (roadSum == 3) // T Pipe
	{
		Pipe result(PipeType::TPIPE);

		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}

		return result;
	}
	else if (roadSum == 2)	// Straight Pipe or L Pipe
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
		else // L Pipe
		{
			Pipe result(PipeType::LPIPE);

			for (int i = 0; i < rand() % 4; i++)
			{
				result.TurnRight();
			}

			return result;
		}
	}
	else // Random Pipe
	{
		Pipe result(rand() % 4);

		for (int i = 0; i < rand() % 4; i++)
		{
			result.TurnRight();
		}

		return result;
	}
}

/**
 * Intent: To determine the type of pipe based on the provided configuration.
 * Pre: None.
 * Post: Returns a Pipe object representing the type of pipe found in the provided configuration.
 * \param src The 2D array representing the configuration of the pipe.
 * \return A Pipe object representing the type of pipe found in the provided configuration.
 */
Pipe Pipe::FindKindPipe(char src[3][3])
{
	// Create Pipe objects for each possible type of pipe
	Pipe StraightPipe(PipeType::STRAIGHTPIPE);
	Pipe TPipe(PipeType::TPIPE);
	Pipe LPipe(PipeType::LPIPE);
	Pipe CrossPipe(PipeType::CROSSPIPE);

	// Check for each type of pipe in the provided configuration
	// Straight Pipe
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

	// T Pipe
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

	// L Pipe
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

	// Cross Pipe
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

/**
 * Intent: To get the type of the pipe.
 * Pre: None.
 * Post: Returns the type of the pipe.
 * \return An integer representing the type of the pipe.
 */
int Pipe::getType()
{
	return type;
}

/**
 * Intent: To get the direction of the pipe.
 * Pre: None.
 * Post: Returns the direction of the pipe.
 * \return An integer representing the direction of the pipe.
 */
int Pipe::getdir()
{
	return dir;
}
