#include <iostream>
#include "levelThree.h"
using namespace std;

LevelThree::LevelThree(string file): Level(3, file){ 
	readFile();
}

char LevelThree::createBlock() {
	if (file != "") { 
		int numBlockFile = blocks.size();
        	if (curBlockIndex == numBlockFile) {
                	curBlockIndex = 0;
        	}
        	char nextBlock = blocks[curBlockIndex];
        	curBlockIndex += 1;
        	return nextBlock;
	}
	int num = rand() % 9;
	char nextBlock;
	if (num == 0 || num == 1) {
		nextBlock = 'S';
	} else if (num == 2 || num == 3) {
		nextBlock = 'Z';
	} else if (num == 4) {
		nextBlock = 'I';
	} else if (num == 5) {
		nextBlock = 'J';
	} else if (num == 6) {
		nextBlock = 'L';
	} else if (num == 7) {
		nextBlock = 'O';
	} else if (num == 8) {
		nextBlock = 'T';
	}
	return nextBlock;
}
