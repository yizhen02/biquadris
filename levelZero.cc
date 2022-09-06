#include <iostream>
#include <fstream>
#include "levelZero.h"
using namespace std;

LevelZero::LevelZero(string file): Level(0,file){
	readFile();
}

char LevelZero::createBlock() {
	int numBlockFile = blocks.size();
	if (curBlockIndex == numBlockFile) {
		curBlockIndex = 0;
	}
	char nextBlock = blocks[curBlockIndex];
	curBlockIndex += 1;
	return nextBlock;
}

