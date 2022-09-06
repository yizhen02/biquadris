#include <iostream>
#include <cstdlib>
#include "levelTwo.h"
using namespace std;

LevelTwo::LevelTwo(): Level(2) {}

char LevelTwo::createBlock() {
	int num = rand() % 7;
	char nextBlock;
	if (num == 0) {
		nextBlock = 'I';
	} else if (num == 1) {
		nextBlock = 'J';
	} else if (num == 2) {
		nextBlock = 'L';
	} else if (num == 3) {
		nextBlock = 'O';
	} else if (num == 4) {
		nextBlock = 'S';
	} else if (num == 5) {
		nextBlock = 'Z';
	} else if (num == 6) {
		nextBlock = 'T';
	}
	return nextBlock;
}
