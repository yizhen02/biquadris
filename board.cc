#include <iostream>
#include <iomanip>
#include "board.h"
#include "cell.h"
#include <vector>
#include "block.h"
#include "score.h"
#include "view.h"
#include "nextBlock.h"
#include "levelZero.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
#include "level.h"
#include <memory>
using namespace std;

//Initiliazes Board
Board::Board(int lev,View * v,Score * s,string file, int horShift, int verShift):
	view{v},blocksCreated{0},
	blind{false}, heavy{false}, force{false}, score{s}, HShift{horShift},
	VShift{verShift}, file{file},endGame{false}{
	specialAvail = false;
	create();
	setCurLevel(lev);
	setNBlock();
	setCrBlock();
	setNBlock();
}

//Destructs
Board::~Board() {
}

void Board::create() {
	//if a previous board exists, clear it first.
	if (map.size() != 0) {
		map.clear();
	}
	// fill up the vector of vectors
	for (int i = 0; i < height; ++i) {
		vector<Cell> v;
		for (int j = 0; j < width; ++j) {
			Cell n;
			n.attachView(view);
			v.emplace_back(n);
		}
		map.emplace_back(v);
	}
}

int Board::getScore() { return score->curScoreGetter(); }

int Board::getHigh() {return score->highScoreGetter();}

void Board::setBlind() { 
	if (blind == false) {
		blind = true;
	}
	for (int i = 2; i < 12; ++i) {
		for(int j = 2; j < 9; ++j) {
			map[i][j].setWhetherBlind(true);
		}
	}
}

void Board::unsetBlind(){
	for (int i = 2; i < 12; ++i) {
                for(int j = 2; j < 9; ++j) {
			map[i][j].setWhetherBlind(false);
                }
        }
	blind = false;
}

bool Board::Blind() { return blind; }

bool Board::Heavy() {return heavy;}

void Board::setHeavy(bool heavy) {
	this->heavy = heavy;
}

bool Board::Force() {return force;}

void Board::setForce(bool force) {this->force = force;}

//bool Board::lost() {return lostt;}

//void Board::setlost(bool l) {this->lostt = l;}

const int Board::getWidth() { return width; }

const int Board::getHeight() { return height; }

void Board::moveBlock(int xShift,int yShift, int rotationShift) {	
	vector<vector<int>> origPos = curBlock->getPosn();
    	for (size_t i = 0; i < origPos.size(); ++i) {
                        map[origPos[i][0]][origPos[i][1]].resetCell();
    	}
	if (xShift != 0) {
		if (xShift > 0) {
			curBlock->rightMove(xShift);
		} else {
			curBlock->leftMove(-1*xShift);
		}
	} else if (rotationShift != 0) {
		if (rotationShift > 0) {
		        curBlock->rotate(true, rotationShift);
		} else {
			curBlock->rotate(false,-1 *rotationShift);
		}
	} else if (yShift > 0) {
		curBlock->downMove(yShift);
	}
	vector<vector<int>> pos = curBlock->getPosn();
    	for (size_t i = 0; i < pos.size(); ++i) {
                 map[pos[i][0]][pos[i][1]].setCell(curBlock->getBlockType());
   	}
}

void Board::resetBoard() //Clears out the board for a restart
{
    for (int i = 0; i < height; i++) {
    	for (int j = 0; j < width; j++) {
    		map[i][j].resetCell();
  	}
    }
}

void Board::setCrBlock()// get current block
{
    if (curBlock != nullptr) {
    	blocks.emplace_back(move(curBlock));
    }
    char nextT = nextBlock->typeGetter();
    curBlock.reset();
    if (nextT == 'I') {
        curBlock = make_unique<IBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'J') {
        curBlock = make_unique<JBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'L') {
        curBlock = make_unique<LBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'O') {
        curBlock = make_unique<OBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'S') {
        curBlock = make_unique<SBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'T') {
        curBlock = make_unique<TBlock>(this,map,heavy,lev->getLevel());
    } else if (nextT == 'Z') {
        curBlock = make_unique<ZBlock>(this,map,heavy,lev->getLevel());
    }
    vector<vector<int>> pos = curBlock->getPosn();
    for (size_t i = 0; i < pos.size(); ++i) {
                        map[pos[i][0]][pos[i][1]].setCell(curBlock->getBlockType());
    }
}

void Board::setNBlock() //get next block
{
     char n = lev->createBlock();
     nextBlock.reset();
     nextBlock = make_unique<NextBlock>(view, n);
}

int Board::getCurLevel() //returns the curLevel
{
    return lev->getLevel();
}

void Board::levelup()
{ 	int curLev = lev->getLevel();
	if (curLev <= 3){
		curLev += 1;
       		setCurLevel(curLev);
	}
}

void Board::drop(){
    vector<vector<int>> origPos = curBlock->getPosn();
    for (size_t i = 0; i < origPos.size(); ++i) {
                        map[origPos[i][0]][origPos[i][1]].resetCell();
    }
    bool success = curBlock->drop();
    vector<vector<int>> pos = curBlock->getPosn();
    for (size_t i = 0; i < pos.size(); ++i) {
                        map[pos[i][0]][pos[i][1]].setCell(curBlock->getBlockType());
    }
    if(blind){
		unsetBlind();
    }
    if (!success) {
    	endGame = true;
	return;
    }
    setCrBlock();
    int n =rowCleared();
    if (n >= 2) specialAvail = true;
    if (n > 0) score->lineCleared(n);
    setNBlock();
    if (lev->getLevel() == 4) lev->countNotClearSetter(lev->countNotClearGetter() + 1);
    if (lev->getLevel() == 4 && lev->countNotClearGetter() == 5) {
    	int y;
	for(int i = 3; i < height; ++i) {
		if (map[i][5].getType() != ' '){
			if(i == 3) {
				endGame = true;				
				break;
			}
			y = i;
		}
	}
	if (!endGame) {
		map[y][5].setCell('*');
	}
	lev->countNotClearSetter(0);
    }
}


void Board::leveldown() {
	int curLev = lev->getLevel();
        if (curLev >= 1){
		curLev -= 1;
                setCurLevel(curLev);
	}
}

vector<vector<Cell>>& Board::getBoard() //Returns reference to theBoard
{
    return map;
}

void Board::setCurLevel(int l) { //......................
	lev.reset();
        if (l == 1) {
                lev = make_unique<LevelOne>();
        } else if (l == 2) {
                lev = make_unique<LevelTwo>();
        } else if (l == 3) {
                lev = make_unique<LevelThree>("");
        } else if (l == 4) {
                lev = make_unique<LevelFour>("");
        } else if (l == 0) {
		lev = make_unique<LevelZero>(file);
	}
        score->levelSetter(l);
}

void Board::random(string file){
	if (lev->getLevel() == 3) {
		lev.reset();
		lev = make_unique<LevelThree>(file);
	} else if (lev->getLevel() == 4){
		lev.reset();
		lev = make_unique<LevelFour>(file);
	}
}

void Board::changeBlock(char c) {
	if (curBlock->getBlockType() != c) {
		blocks.pop_back();
		if (c == 'I') {
        		curBlock = make_unique<IBlock>(this,map,heavy,lev->getLevel());
    		} else if (c == 'J') {
        		curBlock = make_unique<JBlock>(this,map,heavy,lev->getLevel());
    		} else if (c == 'L') {
        		curBlock = make_unique<LBlock>(this,map,heavy,lev->getLevel());
    		} else if (c == 'O') {
        		curBlock = make_unique<OBlock>(this,map,heavy,lev->getLevel());
   		} else if (c == 'S') {
       			curBlock = make_unique<SBlock>(this,map,heavy,lev->getLevel());
    		} else if (c == 'T') {
        		curBlock = make_unique<TBlock>(this,map,heavy,lev->getLevel());
    		} else if (c == 'Z') {
        		curBlock = make_unique<ZBlock>(this,map,heavy,lev->getLevel());
    		}
		blocks.emplace_back(move(curBlock));
	}
}

int Board::rowCleared(){// returns true if clearing two or more rows
	const int cols = 11;
	int count = 0;
	for (int i = 17; i >= 3 ; --i) {
		bool fullRow = true;
		for(int j = 0; j < cols; ++j) {
			if (map[i][j].getType() == ' ') {
				fullRow = false;
				break;
			}
		}
		if (fullRow) {
			removeRow(i);
			++i;
			count += 1;
		}
	}
	return count;
}

void Board::removeRow(int r) {
	for (int i = 0; i < 11; ++i) {
		map[r][i].resetCell();
	}
	for(size_t j = 0; j < blocks.size(); ++j) {
		vector<vector<int>> pos = blocks[j]->getPosn();
		size_t i = 0;
		while(i < pos.size()) {
			if (pos[i][0] == r) {
				pos.erase(pos.begin()+i);
			} else {
				++i;
			}
		}
		if (pos.size() == 0) {
			score->blockCleared(blocks[j]->getLevel());	
		}
	}
	int check_row = r - 1;
	while(check_row > 3) {
		for (auto&b: blocks) {
			vector<vector<int>>& pos = b->getPosn();
			size_t i = 0;
			while (i < pos.size()) {
				if (pos[i][0] == check_row) {
					map[pos[i][0]][pos[i][1]].resetCell();
					pos[i][0] += 1;
					map[pos[i][0]][pos[i][1]].setCell(b->getBlockType());
				}
				++i;
			}
		}
		check_row -= 1;
	}
}

