#include "Pipe.h"
#include "Board.h"

int main()
{
	Board board;
	board.generateMap();
	board.print();
	board.setPipeMap();
}
