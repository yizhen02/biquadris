#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "level.h"
using namespace std;

Level::Level(int level, string file): level{level},curBlockIndex{0},file{file} {
}

int Level::getLevel() {
	return level;
}

void Level::countNotClearSetter(int){
}

int Level::countNotClearGetter(){
	return -1;
}

void Level::readFile(){
        if(file == "") { // check if reads a file name
                //cerr << "No file name";
                return;
        }
        char block;
        ifstream in{file};
        while(in >> block) {
                blocks.emplace_back(block);
        }
}

