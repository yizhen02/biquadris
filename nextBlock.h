#ifndef _NEXTBLOCK_H_
#define _NEXTBLOCK_H_
#include <iostream>
#include <vector>
#include "cell.h"

class View;

class NextBlock{
	char type;
	std::vector<std::vector<Cell>> block;
	public:
	NextBlock(View*, char); // constructor
	~NextBlock(); // destructor
	void typeSetter(char); // set this NextBlock to the specified type
	char typeGetter(); // get this NextBlock's type
	std::vector<std::vector<Cell>>& getBlock(); // get relative positions of all cells of this NextBlock
};

#endif
