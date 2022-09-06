#include <iostream>
#include <cstdlib>
#include "levelFour.h"
#include "level.h"
using namespace std;

LevelFour::LevelFour(string file): Level(4, file){
	readFile();
}

char LevelFour::createBlock(){
	if (file != "") {
                int numBlockFile = blocks.size();
                if (curBlockIndex == numBlockFile) {
                        curBlockIndex = 0;
                }
                char nextBlock = blocks[curBlockIndex];
                curBlockIndex += 1;
                return nextBlock;
        }
	countNotClear += 1;
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

void LevelFour::countNotClearSetter(int n) {
	countNotClear = n;
}

int LevelFour::countNotClearGetter() {
	return countNotClear;
}

