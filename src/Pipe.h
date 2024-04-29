/***********************************************************************
 * File: Pipe.h
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
 * Description: Header file for the Pipe class.
***********************************************************************/

#ifndef _PIPE_H_
#define _PIPE_H_

#include <iostream>

// Declare PipeKind
enum PipeType
{
	STRAIGHTPIPE = 0,
	TPIPE = 1,
	LPIPE = 2,
	CROSSPIPE = 3
};

// Declare direction
enum Dir
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

// Declare Pipe class
class Pipe
{
public:
	// Constructor
	Pipe();
	Pipe(int);

	// Deconstructor
	~Pipe();

	// Pipe function
	void TurnRight();
	void TurnLeft();
	Pipe SetPipe(char up, char right, char down, char left);
	Pipe FindKindPipe(char[3][3]);

	// Get pipe info
	int getType();
	int getdir();

	// Debug function
	void print();

	//Declare Pipe Board
	char pipe[3][3];
private:
	// Declare Pipe Attributes
	int type;
	int dir;
};

#endif // _PIPE_H_
