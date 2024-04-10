#ifndef _PIPE_H_
#define _PIPE_H_

#include <iostream>

enum PipeType
{
	STRAIGHTPIPE = 0,
	TPIPE = 1,
	LPIPE = 2,
	CROSSPIPE = 3
};

enum Dir
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class Pipe
{
public:
	Pipe();
	~Pipe();
	Pipe(int);
	void print();
	void TurnRight();
	void TurnLeft();
	Pipe SetPipe(char up, char right, char down, char left);
	Pipe FindKindPipe(char[3][3]);

	char pipe[3][3];
private:
	int type;
	int dir;
};

#endif // _PIPE_H_
