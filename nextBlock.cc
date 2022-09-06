#include <iostream>
#include "view.h"
#include "nextBlock.h"
using namespace std;

NextBlock::NextBlock(View* v, char t) {
	for (int i = 0; i < 2; ++i) {
		vector<Cell> tmp;
		for(int j = 0; j < 4; ++j) {
			tmp.emplace_back(Cell());
		}
		block.emplace_back(tmp);
	}
	typeSetter(t);
}

NextBlock::~NextBlock() {
	for (int i = 0; i < 2; ++i) {
		block[i].clear();
	}
	block.clear();
}

void NextBlock::typeSetter(char c) {
	type = c;
	for (int i = 0; i < 2; ++i) {
		for(int j = 0; j <4; ++j){
			block[i][j].resetCell();
		}
	}
	if (type == 'I'){
		for(int i = 0; i < 4; ++i) {
			block[1][i].setCell('I');
		}
	} else if (type == 'J'){
		block[0][0].setCell('J');
		for(int i = 0; i < 3; ++i) {
			block[1][i].setCell('J');
		}
	} else if (type == 'L') {
		block[0][2].setCell('L');
                for(int i = 0; i < 3; ++i) {
                        block[1][i].setCell('L');
                }
	} else if (type == 'O') {
		for(int i = 0; i < 2; ++i) {
			block[0][i].setCell('O');
		}
		for(int i = 0; i < 2; ++i) {
			block[1][i].setCell('O');
		}
	} else if (type == 'S') {
		for(int i = 1; i < 3; ++i) {
			block[0][i].setCell('S');
		}
		for(int i = 0; i < 2; ++i) {
			block[1][i].setCell('S');
		}
	} else if (type == 'Z') {
		for(int i = 1; i < 3; ++i) {
                        block[1][i].setCell('Z');
                }
                for(int i = 0; i < 2; ++i) {
                        block[0][i].setCell('Z');
                }
	} else if (type == 'T') {
		for(int i = 0; i < 3; ++i) {
			block[0][i].setCell('T');
		}
		block[1][1].setCell('T');
	}
}

char NextBlock::typeGetter(){
	return type;
}

vector<vector<Cell>>& NextBlock::getBlock(){
	return block;
}


