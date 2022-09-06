#include <iostream>
#include <cstdlib>
#include "levelOne.h"
using namespace std;

LevelOne::LevelOne(): Level(1){}

char LevelOne::createBlock() {
	int num = rand() % 6;
	char nextBlock;
	if (num == 0) {
		if (rand() % 2 == 0) {
			nextBlock = 'S';
		} else {
			nextBlock = 'Z';
		}
	} else if (num == 1) {
		nextBlock = 'I';
	} else if (num == 2) {
		nextBlock = 'J';
	} else if (num == 3) {
		nextBlock = 'L';
	} else if (num == 4) {
		nextBlock = 'O';
	} else if (num == 5) {
		nextBlock = 'T';
	}
	return nextBlock;
}
